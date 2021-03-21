#include "Game.h"

Game::Game()
{}

Game::~Game()
{
    m_player.reset();
    for (int i = 0; i < m_bullets.size(); ++i)
    {
        m_bullets[i].reset();
    }
    for (int i = 0; i < m_asteroids.size(); ++i)
    {
        m_asteroids[i].reset();
    }
    
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
    }
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
    }
    
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

void Game::init_bullets()
{
    m_bullets.init(m_renderer);
}

void Game::init_asteroids()
{
    m_asteroids.init(m_renderer);
}

void Game::init_window(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        m_renderer = SDL_CreateRenderer(m_window, -1, 0);
        if (m_renderer)
        {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 43, 255);
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    SDL_GetWindowSize(m_window, &m_window_width, &m_window_height);
}

void Game::init_player()
{
    m_player = std::make_unique<Player>();
    m_player->init(m_renderer);
    m_player->set_position(Vector2(1, 1));
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    init_window("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    init_player();
    init_bullets();
    init_asteroids();
}

void Game::handleEvents()
{
    using namespace std::chrono;
    auto current_time = system_clock::now();
    duration<float> fs = current_time - m_last_time;
    m_delta = fs.count();
    m_last_time = current_time;
    int mouseX;
    int mouseY;

    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:  
                m_player->change_angle_to(-4.0);
                break;
            case SDLK_RIGHT:
                m_player->change_angle_to(4.0);
                break;
            case SDLK_UP:   
                m_player->speed_up(m_delta, m_window_width, m_window_height);
                break;
            case SDLK_DOWN:  
                m_player->speed_down(m_delta, m_window_width, m_window_height);
                break;
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            case SDLK_SPACE:
                fire_bullet();
                break;
        }
        break;
    case SDL_MOUSEMOTION:
       /* mouse.x = event.motion.x;
        mouse.y = event.motion.y;
        mouse_vec = mouse - m_player->get_center();
        direct_pos = Vector2::make_rotation(m_player->radians());
        ang = Vector2::angle(mouse_vec, direct_pos);
        m_player->change_angle_to(ang);*/
        break;
    case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&mouseX, &mouseY);
        m_player->rotate_to_mouse(Vector2(mouseX, mouseY));
        break;

    default:
        break;
    }
}

void Game::update()
{
    if (m_player->is_forward())
    {
        m_player->move_forward(m_delta, m_window_width, m_window_height, 1);
    }
    else if (!m_player->is_forward())
    {
        m_player->move_forward(m_delta, m_window_width, m_window_height, 2);
    }
    m_bullets.update_fire_bullet(m_window_width, m_window_height, m_delta);
    m_asteroids.update(m_window_width, m_window_height, m_delta);
    update_crossing();
}

void Game::render()
{ 
    SDL_RenderClear(m_renderer);
    m_player->render(m_renderer);
    m_bullets.render(m_renderer);
    m_asteroids.render(m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Game::fire_bullet()
{
    for (int i = 0; i < m_bullets.size(); ++i)
    {
        if (!m_bullets[i]->is_active())
        {
            m_bullets[i]->set_active(true);
            float x = m_player->position().x + m_player->get_width() / 2;
            float y = m_player->position().y + m_player->get_height() / 2;
            Vector2 vector2(x, y);
            m_bullets[i]->set_position(vector2);
            m_bullets[i]->set_radians(m_player->radians());
            break;
        }
    }
}

void Game::update_crossing()
{
    for (int i = 0; i < m_bullets.size(); ++i)
    {
        if (m_bullets[i]->is_active())
        {
            for (int j = 0; j < m_asteroids.size(); ++j)
            {
                Object* obj1 = m_bullets[i].get();
                Object* obj2 = m_asteroids[j].get();
               // Object* obj3 = m_player.get();

                bool iscross = Object::iscrossed(*obj1, *obj2);
                if (iscross)
                {
                    m_asteroids[j]->set_active(false);
                    m_asteroids[j]->set_position(Vector2(0, 0));
                }
            }
        }
    }

    for (int i = 0; i < m_asteroids.size(); ++i)
    {
        Object* obj1 = m_asteroids[i].get();
        Object* obj2 = m_player.get();
        bool iscross = Object::iscrossed(*obj1, *obj2);
        if (iscross)
        {
            m_player->set_active(false);
        }

    }
}