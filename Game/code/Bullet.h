#pragma once

#include "Object.h"

class Bullet : public Object
{
public:
    virtual void init(SDL_Renderer* renderer) override;
};
