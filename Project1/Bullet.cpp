#include "Bullet.h"

class Player;

Bullet::Bullet()
{}

Bullet::~Bullet()
{
    m_image.reset();
}

void Bullet::init(SDL_Renderer* renderer)
{
    const char* path = "assets/bullet.png";
    m_image = std::make_unique<Image>();
    m_image->create_texture(path, renderer);
    m_speed = 500;
    m_radius = radius();
}

