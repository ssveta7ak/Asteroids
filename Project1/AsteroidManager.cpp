#include "AsteroidManager.h"

Asteroidmanager::Asteroidmanager()
{}

Asteroidmanager::~Asteroidmanager()
{}

void Asteroidmanager::init(SDL_Renderer* renderer)
{
    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        mAsteroid = std::make_unique<Asteroid>();
        mAsteroid->init(renderer);
        mAsteroids.at(i) = std::move(mAsteroid);
    }
    mActiveCount = mAsteroids.size();
}

std::unique_ptr<Asteroid>& Asteroidmanager::operator[] (const int index)
{
    return mAsteroids[index];
}

void Asteroidmanager::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        if (mAsteroids[i]->isActive())
        {
            mAsteroids[i]->render(renderer);
        }
    }
}

void Asteroidmanager::update(int window_width, int window_height, float delta)
{
    for (int i = 0; i < mAsteroids.size(); ++i)
    {
        if (mAsteroids[i]->isActive())
        {
            mAsteroids[i]->update(delta, window_width, window_height);
        }
    }

}
