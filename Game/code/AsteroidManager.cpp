#include "AsteroidManager.h"

void AsteroidManager::init(SDL_Renderer *renderer, bool isBig, int count,
                           int width, int height)
{
    for (int i = 0; i < count; ++i)
    {
        // Create and initialize asteroids
        Asteroid asteroid;
        asteroid.init(renderer, isBig, width, height);
        mAsteroids.push_back(std::move(asteroid));
    }
    if (isBig)
    {
        mActiveCount = static_cast<int>(mAsteroids.size());
    }
    else
    {
        mActiveCount = 0;
    }
}

Asteroid &AsteroidManager::operator[](int index) { return mAsteroids[index]; }

void AsteroidManager::render(
        SDL_Renderer *renderer) // Render asteroids which active
{
    for (const Asteroid &asteroid : mAsteroids)
    {
        if (asteroid.isActive())
        {
            asteroid.render(renderer);
        }
    }
}

// Update position of active asteroids
void AsteroidManager::update(int windowWidth, int windowHeight, float delta)
{
    for (Asteroid &asteroid : mAsteroids)
    {
        if (asteroid.isActive())
        {
            asteroid.update(delta, windowWidth, windowHeight);
        }
    }
}

AsteroidManager &AsteroidManager::operator++()
{
    ++mActiveCount;
    return *this;
}

AsteroidManager &AsteroidManager::operator--()
{
    --mActiveCount;
    return *this;
}
