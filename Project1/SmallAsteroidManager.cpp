#include "SmallAsteroidManager.h"

SmallAsteroidManager::SmallAsteroidManager()
{}

SmallAsteroidManager::~SmallAsteroidManager()
{}

void SmallAsteroidManager::init(SDL_Renderer* renderer)
{
    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        mAsteroid = std::make_unique<SmallAsteroid>();
        mAsteroid->init(renderer);
        mAsteroids.at(i) = std::move(mAsteroid);
    }
    mActiveCount = 0;
}

std::unique_ptr<SmallAsteroid>& SmallAsteroidManager::operator[] (const int index)
{
    return mAsteroids[index];
}

void SmallAsteroidManager::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        if (mAsteroids[i]->isActive())
        {
            mAsteroids[i]->render(renderer);
        }
    }
}

void SmallAsteroidManager::update(int window_width, int window_height, float delta)
{
    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        if (mAsteroids[i]->isActive())
        {
            mAsteroids[i]->update(delta, window_width, window_height);
        }
    }
}