#pragma once

#include "Object.h"

class Bullet : public Object
{
public:
    Bullet();
    ~Bullet();

    virtual void init(SDL_Renderer* renderer) override;
};

