#pragma once

class Asteroid;

struct PlayerKilledListner
{
    virtual void onPlayerKilled(const Asteroid& asteroid) = 0;
};

struct AsteroidDestroyedListener
{
    virtual void onAsteroidDestroyed(const Asteroid& asteroid) = 0;
};

struct BulletSpawnListener
{
    virtual void onBulletSpawn() = 0;
};
