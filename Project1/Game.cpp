#include "Game.h"

Game::Game()
{}

Game::~Game()
{
    m_image.reset();
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

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen) 
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
    {
        std::cout << "SDL initialized..." << std::endl;   
        m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_window)
        {
            std::cout << "Window created" << std::endl;
        }
        m_renderer = SDL_CreateRenderer(m_window, -1, 0);
        if (m_renderer)
        {
            SDL_SetRenderDrawColor(m_renderer, 128, 128, 128, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    SDL_GetWindowSize(m_window, &m_window_width, &m_window_height);
    m_image = std::make_unique<Image>();
    m_image->create_texture("assets/player.png", m_renderer);
}

void Game::handleEvents()
{
    using namespace std::chrono;
    auto current_time = system_clock::now();
    duration<float> fs = current_time - m_last_time;
    float delta = fs.count();
    m_last_time = current_time;

    const float SPEED = 5000;
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
            float coordinate;
            case SDLK_LEFT:  
                coordinate = m_x - SPEED * delta;
                m_x = x_inside_window(coordinate);
                break;
            case SDLK_RIGHT:
                coordinate = m_x + SPEED * delta;
                m_x = x_inside_window(coordinate);
                break;
            case SDLK_UP:   
                coordinate = m_y - SPEED * delta;
                m_y = y_inside_window(coordinate);
                break;
            case SDLK_DOWN:  
                coordinate = m_y + SPEED * delta;
                m_y = y_inside_window(coordinate);
                break;
        }
        break;
   default:
        break;
    }
}

void Game::update()
{
    cnt++;
    std::cout << cnt << std::endl;
}

void Game::render()
{
    SDL_Rect dest_rect;
    dest_rect.w = 2 * m_image->width();
    dest_rect.h = 2 * m_image->height();
    dest_rect.x = static_cast<int>(round(m_x));
    dest_rect.y = static_cast<int>(round(m_y));

    m_image->draw_texture(m_renderer, dest_rect);
}

float Game::x_inside_window(float x)
{
    int max_x = m_window_width - 2 * m_image->width();
    x = (x >= max_x) ? max_x : x;
    x = (x < 0) ? 0 : x;
    
    return x;
}

float Game::y_inside_window(float y)
{
    int max_y = m_window_height - 2 * m_image->height();
    y = (y >= max_y) ? max_y : y;
    y = (y < 0) ? 0 : y;
    
    return y;
}