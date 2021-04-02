#pragma once

#include "SDL_mixer.h"
#include "SDL.h"
#include "SDL_image.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <cmath>
#include <windows.h>
#include <sstream>
#include <array>
#include "Player.h"
#include "Bullet.h"
#include "Vector2.h"
#include "BulletManager.h"
#include "AsteroidManager.h"
#include "SmallAsteroid.h"
#include "SmallAsteroidManager.h"
#include "Animation.h"
#include <math.h> 


class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    bool running() const { return isRunning; }
    float getDelta()const { return mDelta; }
    void initBullets();
    void initAsteroids();
    void initPlayer();
    void initAnimation();
    bool initText();
    bool initSound();
    void initWindow(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void fireBullet();
    void updateCrossing();
    void animate();
    void deletePlayer();
    void newGame();

private:
    bool isRunning = false;
    bool mGameFail = false;
    bool mGameWin = false;
    float mDelta = 0;
    int frame = 0;
    SDL_Window* mWindow = nullptr;
    int mWindowWidth;
    int mWindowHeight;
    SDL_Renderer* mRenderer = nullptr;
    std::unique_ptr<Player> mPlayer;
    BulletManager mBullets;
    Asteroidmanager mAsteroids;
    SmallAsteroidManager mSmallAsteroids;
    Animation mAnimation;
    std::unique_ptr<Image> mGameOverText;
    std::unique_ptr<Image> mInstruction;
    std::unique_ptr<Image> mInstruction2;
    std::unique_ptr<Image> mWinText;
    std::chrono::time_point<std::chrono::system_clock> mLastTime = std::chrono::system_clock::now();
    Mix_Music* mShot = nullptr;
    Mix_Music* mExplosion = nullptr;
};
