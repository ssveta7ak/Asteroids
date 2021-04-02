#include "SmallAsteroid.h"

SmallAsteroid::SmallAsteroid()
{}

SmallAsteroid::~SmallAsteroid()
{
    mImage.reset();
}

void SmallAsteroid::init(SDL_Renderer* renderer)
{
    const char* path = "assets/small_asteroid.png";
    mImage = std::make_unique<Image>();
    mImage->createTexture(path, renderer);
    mRadians = randomFloat(0.0, 2 * M_PI);
    mActive = false;
    mSpeed = 40;
    mRadius = radius();
    mPosition = Vector2(-50, -50);
}
