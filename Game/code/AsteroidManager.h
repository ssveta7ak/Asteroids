#pragma once

#include "Asteroid.h"
#include <vector>

class AsteroidManager final
{
public:
    void init(SDL_Renderer* renderer, bool isBig, int count, int width,
              int height);
    void render(SDL_Renderer* renderer);
    void update(int windowWidth, int windowHeight, float delta);
    void setActiveCount(int count) { mActiveCount = count; }
    int activeCount() const { return mActiveCount; }
    int size() const { return (mAsteroids.size()); }
    Asteroid& operator[](const int index);
    AsteroidManager& operator++();
    AsteroidManager& operator--();

    using AsteroidIterator = std::vector<Asteroid>::iterator;
    AsteroidIterator begin() { return mAsteroids.begin(); }
    AsteroidIterator end() { return mAsteroids.end(); }

private:
    int mActiveCount = 0;
    std::vector<Asteroid> mAsteroids;
};
