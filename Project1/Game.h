#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <cmath>
#include "Image.h"
#include <windows.h>

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    bool running() const { return isRunning; }
    float x_inside_window(float x);
    float y_inside_window(float y);

private:
    bool isRunning = false;
    int cnt = 0;
    SDL_Window* m_window = nullptr;
    int m_window_width;
    int m_window_height;
    SDL_Renderer* m_renderer = nullptr;
    std::unique_ptr<Image> m_image;
    float m_x = 0;
    float m_y = 0;
    std::chrono::time_point<std::chrono::system_clock> m_last_time = std::chrono::system_clock::now();
};
