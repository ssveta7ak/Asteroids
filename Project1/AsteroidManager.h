#pragma once

#include <vector>
#include "Asteroid.h"

class AsteroidManager final
{
public:
    void init(SDL_Renderer* renderer, bool isBig, int count, int width, int height);
    void render(SDL_Renderer* renderer);
    void update(int windowWidth, int windowHeight, float delta);
    void setActiveCount(int count) { mActiveCount = count; }
    int activeCount() const { return mActiveCount; }
    int size() const { return static_cast<int>(mAsteroids.size()); }

    Asteroid& operator[] (const int index);
    std::vector<Asteroid>::iterator begin() { return mAsteroids.begin(); }
    std::vector<Asteroid>::iterator end() { return mAsteroids.end(); }

private:
    int mActiveCount = 0;
    std::vector<Asteroid> mAsteroids;
};
