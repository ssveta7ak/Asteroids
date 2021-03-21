#pragma once

#include <array>
#include "Bullet.h"

class BulletManager
{
public:
    BulletManager();
    ~BulletManager();

    void init(SDL_Renderer* renderer);
    int size() { return m_bullets.size(); }
    std::unique_ptr<Bullet>& operator[] (const int index);
    void render(SDL_Renderer* renderer);
    void update_fire_bullet(int window_width, int window_height, float delta);

private:
    std::unique_ptr<Bullet> m_bullet;
    std::array<std::unique_ptr<Bullet>, 10> m_bullets;
};
