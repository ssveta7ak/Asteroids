#pragma once

#include <array>
#include "Asteroid.h"

class Asteroidmanager
{
public:
    Asteroidmanager();
    ~Asteroidmanager();

    void init(SDL_Renderer* renderer);
    int size() { return m_asteroids.size(); }
    std::unique_ptr<Asteroid>& operator[] (const int index);
    void render(SDL_Renderer* renderer);
    void update(int window_width, int window_height, float delta);

private:
    std::unique_ptr<Asteroid> m_asteroid;
    std::array<std::unique_ptr<Asteroid>, 3> m_asteroids;
};
