#include "Game.h"

Game::Game()
{
    mLastTime = std::chrono::system_clock::now();
    mLastTimeBulletSpawn = std::chrono::system_clock::now();
}

Game::~Game()
{
    mPlayer.reset();

    for (std::unique_ptr<Bullet>& bullet: mBullets)
    {
        bullet.reset();
    }

    if (mRenderer)
    {
        SDL_DestroyRenderer(mRenderer);
    }

    if (mWindow)
    {
        SDL_DestroyWindow(mWindow);
    }

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

void Game::initBullets()
{
    mBullets.init(mRenderer);
}

void Game::initAsteroids()
{
    mAsteroids.init(mRenderer, true, 10, mWindowWidth, mWindowHeight);
    mSmallAsteroids.init(mRenderer, false, 30, mWindowWidth, mWindowHeight);
}

void Game::initAnimation()
{
    mAnimation.init(mRenderer);
}

void Game::initWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        mWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
        if (mRenderer)
        {
            SDL_SetRenderDrawColor(mRenderer, 0, 0, 43, 255);
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    SDL_GetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        isRunning = false;
    }
    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        isRunning = false;
    }
}

void Game::initPlayer()
{
    mPlayer = std::make_unique<Player>();
    mPlayer->init(mRenderer);
    mPlayer->setPosition(Vector2(1, 1));
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    initWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen);
    initPlayer();
    initBullets();
    initAsteroids();
    initAnimation();
    mText.init(mRenderer);
    mSound.init();

    mBullets.addListener(&mSound);
    mCollisions.addListener((AsteroidDestroyedListener*)&mSound);
    mCollisions.addListener((AsteroidDestroyedListener*)&mAnimation);
    mCollisions.addListener(this);
    mCollisions.addListener((PlayerKilledListner*)&mSound);
    mCollisions.addListener((PlayerKilledListner*)&mAnimation);
    
}

void Game::handleEvents()
{
    using namespace std::chrono;
    auto timeNow = system_clock::now();
    duration<float> fs = timeNow - mLastTime;
    mDelta = fs.count();
    mLastTime = timeNow;
    float angle = 6.0;
    const float calmDown = 200.0;
    int mouseX;
    int mouseY;
    if (mGameWin)
    {
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
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            case SDLK_RETURN:
                isRunning = true;
                newGame();
                break;
            }
            break;
        default:
            break;
        }
    }
    else if (mPlayer)
    {
        SDL_Event event;
        
        while (SDL_PollEvent(&event) != 0 )
        {
            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_SPACE])
            {
                mPlayer->changeAngleTo(angle);

                auto currentTime = system_clock::now();
                duration<float, std::milli> f = currentTime - mLastTimeBulletSpawn;
                if (f.count() >= calmDown)
                {
                    mLastTimeBulletSpawn = currentTime;
                    fireBullet();
                }
            }
            else if (currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_SPACE])
            {
                 mPlayer->changeAngleTo(-angle);

                 auto currentTime = system_clock::now();
                 duration<float, std::milli> f = currentTime - mLastTimeBulletSpawn;
                 if (f.count() >= calmDown)
                 {
                     mLastTimeBulletSpawn = currentTime;
                     fireBullet();
                 }
            }
            else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_SPACE])
            {
                mPlayer->speedUp(mDelta, mWindowWidth, mWindowHeight);

                auto currentTime = system_clock::now();
                duration<float, std::milli> f = currentTime - mLastTimeBulletSpawn;
                if (f.count() >= calmDown)
                {
                    mLastTimeBulletSpawn = currentTime;
                    fireBullet();
                }
            }
            else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_SPACE])
            {
                mPlayer->speedDown(mDelta, mWindowWidth, mWindowHeight);

                auto currentTime = system_clock::now();
                duration<float, std::milli> f = currentTime - mLastTimeBulletSpawn;
                if (f.count() >= calmDown)
                {
                    mLastTimeBulletSpawn = currentTime;
                    fireBullet();
                }
            }
            else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT])
            {
                 mPlayer->changeAngleTo(-angle);
                 mPlayer->speedDown(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                 mPlayer->changeAngleTo(angle);
                 mPlayer->speedDown(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT])
            {
                 mPlayer->changeAngleTo(-angle);
                 mPlayer->speedUp(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                 mPlayer->changeAngleTo(angle);
                 mPlayer->speedUp(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_LEFT])
            {
                mPlayer->changeAngleTo(-angle);
              //  mPlayer->goRight(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                mPlayer->changeAngleTo(angle);
              //  mPlayer->goLeft(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_UP])
            {
                mPlayer->speedUp(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_DOWN])
            {
                mPlayer->speedDown(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_SPACE])
            {
                auto currentTime = system_clock::now();
                duration<float, std::milli> f = currentTime - mLastTimeBulletSpawn;
                if (f.count() >= calmDown)
                {
                    mLastTimeBulletSpawn = currentTime;
                    fireBullet();
                }
                
            }
            else if (currentKeyStates[SDL_SCANCODE_ESCAPE])
            {
                isRunning = false;
            }

            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
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
                mPlayer->rotateToMouse(Vector2(mouseX, mouseY));
                break;

            default:
                break;
            }
        }
    }
    else // Game fail
    {
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
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            case SDLK_RETURN:
                isRunning = true;
                mGameFail = false;
                initPlayer();
                break;
            }
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    if (mSmallAsteroids.activeCount() == 0 && mAsteroids.activeCount() == 0)
    {
        mGameWin = true;
        for (std::unique_ptr<Bullet>& bullet: mBullets)
        {
            bullet->setActive(false);
        }
        return;
    }
    mBullets.updateFireBullet(mWindowWidth, mWindowHeight, mDelta);
    mAsteroids.update(mWindowWidth, mWindowHeight, mDelta);
    mSmallAsteroids.update(mWindowWidth, mWindowHeight, mDelta);
    if (mPlayer)
    {
        if (mPlayer->isForward())
        {
            mPlayer->moveForward(mDelta, mWindowWidth, mWindowHeight, 1);
        }
        else
        {
            mPlayer->moveForward(mDelta, mWindowWidth, mWindowHeight, 2);
        }
        mCollisions.update(mBullets, mAsteroids, mSmallAsteroids, *mPlayer);
    }
}

void Game::render()
{ 
    SDL_RenderClear(mRenderer);
    
    mBullets.render(mRenderer);
    mAsteroids.render(mRenderer);
    mSmallAsteroids.render(mRenderer);
    mAnimation.animate();
    
    if (mGameFail)
    {
        int x1 = mWindowWidth / 2 - mText.GameOverText()->width() / 2;
        int y1 = mWindowHeight / 2 - mText.GameOverText()->height();
        mText.render(mRenderer, mText.GameOverText(), x1, y1);

        int x2 = mWindowWidth / 2 - mText.Instruction2()->width() / 2;
        int y2 = mWindowHeight - mText.Instruction2()->height();
        mText.render(mRenderer, mText.Instruction2(), x2, y2);
    }
    else if (mGameWin)
    {
        int x1 = mWindowWidth / 2 - mText.WinText()->width() / 2;
        int y1 = (mWindowHeight / 2) - mText.WinText()->height();
        mText.render(mRenderer, mText.WinText(), x1, y1);

        int x2 = mWindowWidth / 2 - mText.Instruction()->width() / 2;
        int y2 = mWindowHeight - mText.Instruction()->height();
        mText.render(mRenderer, mText.Instruction(), x2, y2);

    }
    else if (mPlayer)
    {
        mPlayer->render(mRenderer);
    }
    
    SDL_RenderPresent(mRenderer);
}

void Game::fireBullet()
{
    Bullet* bullet = mBullets.spawnBullet();
    bullet->setPosition(mPlayer->center());
    bullet->setAngle(mPlayer->angle());
}

void Game::deletePlayer()
{
    mPlayer.reset();
}

void Game::newGame()
{
    mGameWin = false;
    mGameFail = false;
    initPlayer();
    for ( Asteroid& asteroid : mAsteroids)
    {
        asteroid.setActive(true);
        asteroid.setAngle(Asteroid::randomFloat(0.0, 2 * M_PI));
        float  a = Object::randomFloat(0.0, mWindowWidth);
        float  b = Object::randomFloat(0.0, mWindowHeight);
        asteroid.setPosition(Vector2(a, b));
    }
    mAsteroids.setActiveCount(mAsteroids.size());
    mSmallAsteroids.setActiveCount(0);
}

void Game::onPlayerKilled(const Asteroid& asteroid)
{
    deletePlayer();
    mGameFail = true;
}