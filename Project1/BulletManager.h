#pragma once

#include <array>
#include <vector>
#include "Bullet.h"
#include "Listener.h"

class BulletManager final
{
public:

    void init(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);
    void updateFireBullet(int windowWidth, int windowHeight, float delta);
    int size() const { return static_cast<int>(mBullets.size()); }
    Bullet* spawnBullet();

    std::unique_ptr<Bullet>& operator[] (const int index);
    std::array<std::unique_ptr<Bullet>, 100>::iterator begin() { return mBullets.begin(); }
    std::array<std::unique_ptr<Bullet>, 100>::iterator end() { return mBullets.end(); }
    
    void addListener(BulletSpawnListener* listener) { mBulletSpawnListener.push_back(listener); }

private:
    std::array<std::unique_ptr<Bullet>, 100> mBullets;
    std::vector<BulletSpawnListener*> mBulletSpawnListener;
};
