#pragma once

#include "Animation.h"
#include "AnimationManager.h"
#include "AsteroidManager.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "CollisionManager.h"
#include "Listener.h"
#include "Player.h"
#include "Settings.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "Vector2.h"
#include <chrono>
#include <memory>

class Game : public PlayerKilledListner
{
public:
    Game();
    ~Game();

    void init(const char *title);
    void handleEvents();
    void update();
    void render();
    void renderText();
    void qiut() { isRunning = false; }

    bool running() const { return isRunning; }
    float getDelta() const { return mDelta; }

    void initBullets();
    void initAsteroids();
    void initPlayer();
    void initAnimation();
    void initWindow(const char *title, int xpos, int ypos, int width,
                    int height, bool fullscreen);

    void fireBullet();
    void deletePlayer();
    void newGame();

    virtual void onPlayerKilled(const Asteroid &asteroid) override;

private:
    bool isRunning = false;
    bool mGameFail = false;
    bool mGameWin = false;
    bool mIsCrossed = false;

    float mDelta = 0;
    SDL_Window *mWindow = nullptr;
    int mWindowWidth;
    int mWindowHeight;
    SDL_Renderer *mRenderer = nullptr;
    std::unique_ptr<Player> mPlayer;

    Settings settings;
    BulletManager mBullets;
    AsteroidManager mAsteroids;
    AsteroidManager mSmallAsteroids;
    AnimationManager mAnimation;
    SoundManager mSound;
    CollisionManager mCollisions;
    UIManager mText;

    using time_point = std::chrono::time_point<std::chrono::system_clock>;
    time_point mLastTime;
    time_point mLastTimeBulletSpawn;
};
