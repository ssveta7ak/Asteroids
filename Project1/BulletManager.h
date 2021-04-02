#pragma once

#include <array>
#include "Bullet.h"

class BulletManager
{
public:
    BulletManager();
    ~BulletManager();

    void init(SDL_Renderer* renderer);
    int size() { return mBullets.size(); }
    std::unique_ptr<Bullet>& operator[] (const int index);
    void render(SDL_Renderer* renderer);
    void updateFireBullet(int window_width, int window_height, float delta);

private:
    std::unique_ptr<Bullet> mBullet;
    std::array<std::unique_ptr<Bullet>, 20> mBullets;
};
