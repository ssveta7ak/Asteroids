#pragma once

#include "Asteroid.h"

class SmallAsteroid : public Asteroid
{
public:
    SmallAsteroid();
    virtual ~SmallAsteroid() override;

    virtual void init(SDL_Renderer* renderer) override;
};