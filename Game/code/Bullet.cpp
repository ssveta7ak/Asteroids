#include "Bullet.h"

void Bullet::init(SDL_Renderer* renderer)
{
    const char* path = "assets/textures/bullet.png";
    mImage = std::make_unique<Image>();
    mImage->createTexture(path, renderer);
    mSpeed = 500;
    mRadius = radius();
}
