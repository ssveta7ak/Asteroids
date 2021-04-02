#pragma once

#include <array>
#include <random>
#include "Asteroid.h"

class Asteroidmanager
{
public:
    Asteroidmanager();
    virtual ~Asteroidmanager();

    void init(SDL_Renderer* renderer);
    int size() { return mAsteroids.size(); }
    std::unique_ptr<Asteroid>& operator[] (const int index);
    void render(SDL_Renderer* renderer);
    void update(int window_width, int window_height, float delta);
    int mActiveCount;

private:
    std::unique_ptr<Asteroid> mAsteroid;
    std::array<std::unique_ptr<Asteroid>, 10> mAsteroids;
};
