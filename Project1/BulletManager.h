#pragma once

#include "Bullet.h"
#include "Listener.h"
#include <array>
#include <vector>

class BulletManager final
{
public:
    void init(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer);
    void updateFireBullet(int windowWidth, int windowHeight, float delta);
    int size() const { return static_cast<int>(mBullets.size()); }
    Bullet *spawnBullet();
    std::unique_ptr<Bullet> &operator[](const int index);

    using BulletIterator = std::array<std::unique_ptr<Bullet>, 100>::iterator;
    BulletIterator begin() { return mBullets.begin(); }
    BulletIterator end() { return mBullets.end(); }

    void addListener(BulletSpawnListener *listener)
    {
        mBulletSpawnListener.push_back(listener);
    }

private:
    static constexpr int COUNT = 100;
    std::array<std::unique_ptr<Bullet>, COUNT> mBullets;
    std::vector<BulletSpawnListener *> mBulletSpawnListener;
};
