#pragma once

#include "SDL.h"
#include <iostream>
#include "Image.h"
#include "Player.h"
#include "Vector2.h"
#include "Object.h"


class Bullet : public Object
{
public:
    Bullet();
    ~Bullet();

    void init(SDL_Renderer* renderer);

private:
  
};

