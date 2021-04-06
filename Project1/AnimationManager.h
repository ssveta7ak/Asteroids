#pragma once
#include "Listener.h"
#include "Animation.h"


class Asteroid;

class AnimationManager final 
    : public PlayerKilledListner
    , public AsteroidDestroyedListener
{
public:
    void init(SDL_Renderer* renderer);
    void animate();

private:
    virtual void onPlayerKilled(const Asteroid& asteroid) override;
    virtual void onAsteroidDestroyed(const Asteroid& asteroid) override;

    SDL_Renderer* mRenderer = nullptr;
    Animation mAnimation;
    int frame = 0;
};
