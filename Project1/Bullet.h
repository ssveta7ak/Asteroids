#pragma once

#include "Object.h"

class Bullet : public Object
{
public:
    Bullet() = default;
    ~Bullet();

    virtual void init(SDL_Renderer* renderer) override;
};

