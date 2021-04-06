#pragma once

#include "BulletManager.h"
#include "AsteroidManager.h"
#include "Player.h"

class CollisionManager final
{
public:
    void update(BulletManager& bullets, AsteroidManager& asteroids,
                AsteroidManager& smallAsteroids, Player& player);

    void addListener(AsteroidDestroyedListener* listener) { mAsteroidDestroyedListener.push_back(listener); }
    void addListener(PlayerKilledListner* listener) { mPlayerKilledListener.push_back(listener); }

private:
    std::vector<AsteroidDestroyedListener*> mAsteroidDestroyedListener;
    std::vector<PlayerKilledListner*> mPlayerKilledListener;
};
