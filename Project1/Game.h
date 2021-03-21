#pragma once

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
    float get_delta()const { return m_delta; }
    void init_bullets();
    void init_asteroids();
    void init_player();
    void init_window(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void fire_bullet();
    void update_crossing();

private:
    bool isRunning = false;
    float m_delta = 0;
    int cnt = 0;
    SDL_Window* m_window = nullptr;
    int m_window_width;
    int m_window_height;
    SDL_Renderer* m_renderer = nullptr;
    std::unique_ptr<Player> m_player;
    BulletManager m_bullets;
    Asteroidmanager m_asteroids;
    std::chrono::time_point<std::chrono::system_clock> m_last_time = std::chrono::system_clock::now();
};
