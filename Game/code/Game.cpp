#include "Game.h"

Game::Game()
{
    // Initialize time members
    mLastTime = std::chrono::system_clock::now();
    mLastTimeBulletSpawn = std::chrono::system_clock::now();
    mUpdateTime = std::chrono::system_clock::now();
}

Game::~Game()
{
    // Free resources
    mPlayer.reset();

    for (std::unique_ptr<Bullet>& bullet : mBullets)
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
}

void Game::initBullets()
{
    // Create and init bullets
    mBullets.init(mRenderer);
}

void Game::initAsteroids()
{
    // Create and init asteroids inside game window
    mAsteroids.init(mRenderer, true, 15, mWindowWidth, mWindowHeight);
    mSmallAsteroids.init(mRenderer, false, 35, mWindowWidth, mWindowHeight);
}

void Game::initAnimation() { mAnimation.init(mRenderer); }

void Game::initWindow(const char* title, int xpos, int ypos, int width,
                      int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // Create window with custom dimensions
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
        // Exit the game if window won't create
        isRunning = false;
    }
    SDL_GetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);

    // Initialize  SDL_TTF for using TrueType fonts, exit the game if it won't
    // be created
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
               TTF_GetError());
        isRunning = false;
    }
    // Initialize SDL_mixer for using sound effects, exit the game if it won't
    // be created
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
               Mix_GetError());
        isRunning = false;
    }
}

void Game::initPlayer()
{
    // Create and initialize player
    mPlayer = std::make_unique<Player>();
    mPlayer->init(mRenderer);
    mPlayer->setPosition(Vector2(1, 1));
}

void Game::init(const char* title)
{
    settings.init("assets/settings/settings.json");
    initWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
               settings.width(), settings.height(), settings.fullscreen());
    initPlayer();
    initBullets();
    initAsteroids();
    initAnimation();
    mText.init(mRenderer);
    mSound.init();

    // Add event listeners
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
    float angle = 6.0;            // Delta angle (in degrees) of rotation
    const float calmDown = 200.0; // Timeout between bullets spawn
    int mouseX;
    int mouseY;

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        const uint8_t* currentKeyStates = SDL_GetKeyboardState(nullptr);
        if (mPlayer)
        {
            if (currentKeyStates[SDL_SCANCODE_LEFT])
            {
                mPlayer->changeAngleTo(-angle);
            }
            if (currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                mPlayer->changeAngleTo(angle);
            }
            if (currentKeyStates[SDL_SCANCODE_UP])
            {
                mPlayer->speedUp(mDelta, mWindowWidth, mWindowHeight);
            }
            if (currentKeyStates[SDL_SCANCODE_DOWN])
            {
                mPlayer->speedDown(mDelta, mWindowWidth, mWindowHeight);
            }
            if (currentKeyStates[SDL_SCANCODE_SPACE])
            {
                auto currentTime = system_clock::now();
                duration<float, std::milli> f =
                        currentTime - mLastTimeBulletSpawn;
                if (f.count() >= calmDown)
                {
                    mLastTimeBulletSpawn = currentTime;
                    fireBullet();
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                mPlayer->rotateToMouse(Vector2(mouseX, mouseY));
            }
        }
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (currentKeyStates[SDL_SCANCODE_ESCAPE])
        {
            isRunning = false;
        }
        if (currentKeyStates[SDL_SCANCODE_RETURN])
        {
            if (mGameWin)
            {
                isRunning = true;
                newGame();
                break;
            }
            else if (mGameFail)
            {
                isRunning = true;
                mGameFail = false;
                initPlayer();
                break;
            }
        }
    }
}
QuadtreeNode Game::createQuadTree()
{
    Rect boundary = Rect(settings.width() / 2, settings.height() / 2,
                         settings.width() / 2, settings.height() / 2);

    QuadtreeNode qtree = QuadtreeNode(boundary, 8);
    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        qtree.insert(mAsteroids[i]);
    }
    for (int i = 0; i < mSmallAsteroids.size(); ++i)
    {
        qtree.insert(mSmallAsteroids[i]);
    }
    return qtree;
}


void Game::update()
{
    using namespace std::chrono;
    auto time_cur = system_clock::now();
    duration<float> ft = time_cur - mUpdateTime;
    float delta = ft.count();
    mUpdateTime = time_cur;

    QuadtreeNode qtree = createQuadTree();
   
    if (mSmallAsteroids.activeCount() == 0 && mAsteroids.activeCount() == 0)
    {
        // Game won when all asteroids are destroyed
        mGameWin = true;

        // Set all bullets inactive
        for (std::unique_ptr<Bullet>& bullet : mBullets)
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
        // Check objects collisions
        //mCollisions.update(mBullets, mAsteroids, mSmallAsteroids, *mPlayer);

        // Check objects collisions using Quadtree
        mCollisions.qtree_update(qtree, mBullets, mAsteroids, mSmallAsteroids,
                                 *mPlayer);
    }
}

void Game::renderText()
{
    if (mGameFail)
    {
        // Render text in the center of game window.
        // Calculate coordinates (x1, y1) of the window center
        int x1 = mWindowWidth / 2 - mText.GameOverText()->width() / 2;
        int y1 = mWindowHeight / 2 - mText.GameOverText()->height();
        mText.render(mRenderer, mText.GameOverText(), x1, y1);

        // Render text in the bottom of the window
        int x2 = mWindowWidth / 2 - mText.Instruction2()->width() / 2;
        int y2 = mWindowHeight - mText.Instruction2()->height();
        mText.render(mRenderer, mText.Instruction2(), x2, y2);
    }
    else if (mGameWin)
    {
        // Render text in the center of game window
        // Calculate coordinates (x1, y1) of the window center
        int x1 = mWindowWidth / 2 - mText.WinText()->width() / 2;
        int y1 = (mWindowHeight / 2) - mText.WinText()->height();
        mText.render(mRenderer, mText.WinText(), x1, y1);

        // Render text in the bottom of the window
        int x2 = mWindowWidth / 2 - mText.Instruction()->width() / 2;
        int y2 = mWindowHeight - mText.Instruction()->height();
        mText.render(mRenderer, mText.Instruction(), x2, y2);
    }
}

void Game::render()
{
    SDL_RenderClear(mRenderer);

    mBullets.render(mRenderer);
    mAsteroids.render(mRenderer);
    mSmallAsteroids.render(mRenderer);
    mAnimation.animate();
    renderText();
    if (mPlayer && !mGameWin)
    {
        mPlayer->render(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
}

void Game::fireBullet()
{
    // Set active bullet. Position and angle are taken from Player.
    Bullet* bullet = mBullets.spawnBullet();
    bullet->setPosition(mPlayer->center());
    bullet->setAngle(mPlayer->angle());
}

void Game::deletePlayer() { mPlayer.reset(); }

void Game::newGame()
{
    mGameWin = false;
    mGameFail = false;
    initPlayer();

    // Activate all asteroids, set random positions inside the window
    for (Asteroid& asteroid : mAsteroids)
    {
        asteroid.setActive(true);
        asteroid.setAngle(Asteroid::randomFloat(0.0, 2 * M_PI));
        float a = Object::randomFloat(0.0, mWindowWidth);
        float b = Object::randomFloat(0.0, mWindowHeight);
        asteroid.setPosition(Vector2(a, b));
    }
    mAsteroids.setActiveCount(mAsteroids.size());
    mSmallAsteroids.setActiveCount(0);
}

// Delete player when objects collision is happened
void Game::onPlayerKilled(const Asteroid& asteroid)
{
    deletePlayer();
    mGameFail = true;
}