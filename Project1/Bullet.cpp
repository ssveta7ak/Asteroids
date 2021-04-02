#include "Bullet.h"

Bullet::Bullet()
{}

Bullet::~Bullet()
{
    mImage.reset();
}

void Bullet::init(SDL_Renderer* renderer)
{
    const char* path = "assets/bullet.png";
    mImage = std::make_unique<Image>();
    mImage->createTexture(path, renderer);
    mSpeed = 500;
    mRadius = radius();
}
