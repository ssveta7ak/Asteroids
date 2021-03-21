#pragma once

#include "SDL.h"
#include <iostream>
#include <random>
#include "Image.h"
#include "Vector2.h"
#include "Object.h"

class Asteroid: public Object
{
public:
    Asteroid();
    virtual ~Asteroid() override;

    virtual void init(SDL_Renderer* renderer) override;
    Vector2 is_inside_window(Vector2 position, int window_width, int window_height);
    void update(float delta, int window_width, int window_height);

private:
    float random_float(float a, float b);
};
