#pragma once

#include "SDL_mixer.h"
#include <stdio.h>
#include "Listener.h"


class SoundManager final 
    : public BulletSpawnListener
    , public PlayerKilledListner
    , public AsteroidDestroyedListener
{
public:
    
    ~SoundManager();

    bool init();

private:
    virtual void onPlayerKilled(const Asteroid& asteroid) override { Mix_PlayMusic(mExplosion, 1); }
    virtual void onBulletSpawn() override { Mix_PlayMusic(mShot, 1); }
    virtual void onAsteroidDestroyed(const Asteroid& asteroid) override { Mix_PlayMusic(mExplosion, 1); }
    
    Mix_Music* mShot = nullptr;
    Mix_Music* mExplosion = nullptr;
};
