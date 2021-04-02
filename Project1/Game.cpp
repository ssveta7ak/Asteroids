#include "Game.h"

Game::Game()
{}

Game::~Game()
{
    mPlayer.reset();
    mAnimation.reset();
    mGameOverText.reset();
    mInstruction.reset();
    mInstruction2.reset();
    mWinText.reset();
    Mix_FreeMusic(mShot);
    Mix_FreeMusic(mExplosion);

    for (int i = 0; i < mBullets.size(); ++i)
    {
        mBullets[i].reset();
    }

    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        mAsteroids[i].reset();
    }

    for (int i = 0; i < mSmallAsteroids.size(); ++i)
    {
        mSmallAsteroids[i].reset();
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
    mAsteroids.init(mRenderer);
    mSmallAsteroids.init(mRenderer);
}

void Game::initAnimation()
{
    mAnimation.init(mRenderer);
}

bool Game::initText()
{
    bool success = true;
    SDL_Color textColor = { 255, 0, 0 };
    mGameOverText = std::make_unique<Image>();
    if (!mGameOverText->createFromRenderedText("GAME OVER", textColor, 70, mRenderer))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    textColor = { 255, 255, 255 };
    mInstruction = std::make_unique<Image>();
    if (!mInstruction->createFromRenderedText("ESCAPE:  Exit Game             SPACE:  New Game", textColor, 25, mRenderer))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    textColor = { 255, 255, 255 };
    mInstruction2 = std::make_unique<Image>();
    if (!mInstruction2->createFromRenderedText("ESCAPE:  Exit Game             SPACE:  Continue", textColor, 25, mRenderer))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    textColor = { 0, 255, 0 };
    mWinText = std::make_unique<Image>();
    if (!mWinText->createFromRenderedText("YOU WIN!", textColor, 70, mRenderer))
    {
        printf("Failed to render text texture!\n");
        success = false;
    }
    return success;
}

bool Game::initSound()
{
    bool success = true;
    //Load sound effects
    mShot = Mix_LoadMUS("assets/sound/shot.wav");
    if (!mShot)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    mExplosion = Mix_LoadMUS("assets/sound/explosion.wav");
    if (!mExplosion)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
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
    initWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    initPlayer();
    initBullets();
    initAsteroids();
    initAnimation();
    initText();
    initSound();
}

void Game::handleEvents()
{
    using namespace std::chrono;
    auto current_time = system_clock::now();
    duration<float> fs = current_time - mLastTime;
    mDelta = fs.count();
    mLastTime = current_time;
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
            case SDLK_SPACE:
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
                mPlayer->changeAngleTo(4.0);
                fireBullet();
                Mix_PlayMusic(mShot, 1);
            }
            else if (currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_SPACE])
            {
                 mPlayer->changeAngleTo(-4.0);
                 fireBullet();
                 Mix_PlayMusic(mShot, 1);
            }
            else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_LEFT])
            {
                  mPlayer->changeAngleTo(-4.0);
                 mPlayer->speedDown(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_DOWN] && currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                 mPlayer->changeAngleTo(4.0);
                 mPlayer->speedDown(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_LEFT])
            {
                 mPlayer->changeAngleTo(-4.0);
                 mPlayer->speedUp(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                 mPlayer->changeAngleTo(4.0);
                 mPlayer->speedUp(mDelta, mWindowWidth, mWindowHeight);
            }
            else if (currentKeyStates[SDL_SCANCODE_LEFT])
            {
                mPlayer->changeAngleTo(-4.0);
            }
            else if (currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                mPlayer->changeAngleTo(4.0);
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
                fireBullet();
                Mix_PlayMusic(mShot, 1);
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
            /*case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                      mPlayer->changeAngleTo(-4.0);
                    break;
                case SDLK_RIGHT:
                    mPlayer->changeAngleTo(4.0);
                    break;
                case SDLK_UP:
                    mPlayer->speedUp(mDelta, mWindowWidth, mWindowHeight);
                    break;
                case SDLK_DOWN:
                    mPlayer->speedDown(mDelta, mWindowWidth, mWindowHeight);
                    break;
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                case SDLK_SPACE:
                    fireBullet();
                    Mix_PlayMusic(mShot, 1);
                    break;
                }
                break;*/
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
    else
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
            case SDLK_SPACE:
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
    if (mSmallAsteroids.mActiveCount == 0 && mAsteroids.mActiveCount == 0)
    {
        mGameWin = true;
        for (int i = 0; i < mBullets.size(); ++i)
        {
            mBullets[i]->setActive(false);
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
        updateCrossing();
    }
}

void Game::render()
{ 
    SDL_RenderClear(mRenderer);
    
    mBullets.render(mRenderer);
    mAsteroids.render(mRenderer);
    mSmallAsteroids.render(mRenderer);
    animate();
    
    
    if (mGameFail)
    {
        SDL_Rect dest_rect;
        dest_rect.w = mGameOverText->width();
        dest_rect.h = mGameOverText->height();
        dest_rect.x = 170;
        dest_rect.y = 200;

        mGameOverText->render(mRenderer, dest_rect);

        SDL_Rect dest_rect2;
        dest_rect2.w = mInstruction2->width();
        dest_rect2.h = mInstruction2->height();
        dest_rect2.x = 100;
        dest_rect2.y = 550;

        mInstruction2->render(mRenderer, dest_rect2);
    }
    else if (mGameWin)
    {
        SDL_Rect dest_rect;
        dest_rect.w = mWinText->width();
        dest_rect.h = mWinText->height();
        dest_rect.x = 170;
        dest_rect.y = 200;

        mWinText->render(mRenderer, dest_rect);

        SDL_Rect dest_rect2;
        dest_rect2.w = mInstruction->width();
        dest_rect2.h = mInstruction->height();
        dest_rect2.x = 100;
        dest_rect2.y = 550;

        mInstruction->render(mRenderer, dest_rect2);

    }
    else if (mPlayer)
    {
        mPlayer->render(mRenderer);
    }
    
    SDL_RenderPresent(mRenderer);
}

void Game::fireBullet()
{
    for (int i = 0; i < mBullets.size(); ++i)
    {
        if (!mBullets[i]->isActive())
        {
            mBullets[i]->setActive(true);
            mBullets[i]->setPosition(mPlayer->center());
            mBullets[i]->setRadians(mPlayer->radians());
            break;
        }
    }
}

void Game::updateCrossing()
{
    //check crossing bullet and asteroid
    for (int i = 0; i < mBullets.size(); ++i)
    {
        if (mBullets[i]->isActive())
        {
            for (int j = 0; j < mAsteroids.size(); ++j)
            {
                Object* obj1 = mBullets[i].get();
                Object* obj2 = mAsteroids[j].get();

                bool iscross = Object::iscrossed(*obj1, *obj2);
                if (iscross)
                {
                     Mix_PlayMusic(mExplosion, 1);
                    mAnimation.isActive = true;
                    mAnimation.setPosition(mAsteroids[j]->position());

                    //create two small asteroids after destruction big asteroid
                    for (int k = 0; k < mSmallAsteroids.size(); ++k)
                    {
                        if (!mSmallAsteroids[k]->isActive())
                        {
                            mSmallAsteroids[k]->setActive(true);
                            mSmallAsteroids[k]->setPosition(mAsteroids[j]->position());
                            ++mSmallAsteroids.mActiveCount;
                            for (int t = k; t < mSmallAsteroids.size(); ++t)
                            {
                                if (!mSmallAsteroids[t]->isActive())
                                {
                                    mSmallAsteroids[t]->setActive(true);
                                    mSmallAsteroids[t]->setPosition(mAsteroids[j]->position());
                                    ++mSmallAsteroids.mActiveCount;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    --mAsteroids.mActiveCount;
                     mAsteroids[j]->reset();
                    mBullets[i]->reset();
                    break;
                }
            }
        }
       
    }

    //check crossing bullet and small asteroid
    for (int i = 0; i < mBullets.size(); ++i)
    {
        if (mBullets[i]->isActive())
        {
            for (int j = 0; j < mSmallAsteroids.size(); ++j)
            {
                if (mSmallAsteroids[j]->isActive())
                {
                    Object* obj1 = mBullets[i].get();
                    Object* obj2 = mSmallAsteroids[j].get();

                    bool iscross = Object::iscrossed(*obj1, *obj2);
                    if (iscross)
                    {
                        Mix_PlayMusic(mExplosion, 1);
                        mAnimation.isActive = true;
                        mAnimation.setPosition(mSmallAsteroids[j]->position());
                        --mSmallAsteroids.mActiveCount;
                         mSmallAsteroids[j]->reset();
                        mBullets[i]->reset();
                        break;
                    }
                }
            }
        }
    }

    //check crossing player and asteroid
    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        if (mPlayer->isActive())
        {
            Object* obj1 = mAsteroids[i].get();
            Object* obj2 = mPlayer.get();
            bool iscross = Object::iscrossed(*obj1, *obj2);
            if (iscross)
            {
                Mix_PlayMusic(mExplosion, 1);
                deletePlayer();
                mAnimation.isActive = true;
                mAnimation.setPosition(mAsteroids[i]->position());
                --mAsteroids.mActiveCount;
                mAsteroids[i]->reset();
                mGameFail = true;
                return;
            }
        }
    }

    //check crossing player and small asteroid
    for (int i = 0; i < mSmallAsteroids.size(); ++i)
    {
        if (mSmallAsteroids[i]->isActive() && mPlayer->isActive())
        {
            Object* obj1 = mSmallAsteroids[i].get();
            Object* obj2 = mPlayer.get();
            bool iscross = Object::iscrossed(*obj1, *obj2);
            if (iscross)
            {
                Mix_PlayMusic(mExplosion, 1);
                deletePlayer();
                mAnimation.isActive = true;
                mAnimation.setPosition(mSmallAsteroids[i]->position());
                --mSmallAsteroids.mActiveCount;
                mSmallAsteroids[i]->reset();
                mGameFail = true;
                return;
            }
        }
    }
}



void Game::animate()
{
    if (mAnimation.isActive && mAnimation.mDuration > 0)
    {
        //Renmder current frame
        SDL_Rect* currentClip = &mAnimation.mSpriteClips[frame / 3];
        mAnimation.render(mRenderer, mAnimation.position().x, mAnimation.position().y, currentClip);
        ++frame;

        //Cycle animation
        if (frame / 3 >= mAnimation.ANIMATION_FRAMES)
        {
            frame = 0;
        }
        --mAnimation.mDuration;
    }
    else if (mAnimation.mDuration <= 0)
    {
        mAnimation.reset();
    }
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
    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        mAsteroids[i]->setActive(true);
        mAsteroids[i]->setRadians(Asteroid::randomFloat(0.0, 2 * M_PI));
        float  a = Asteroid::randomFloat(0.0, 800.0);
        float  b = Asteroid::randomFloat(0.0, 600.0);
        mAsteroids[i]->setPosition(Vector2(a, b));
    }
    mAsteroids.mActiveCount = mAsteroids.size();
    mSmallAsteroids.mActiveCount = 0;
}
