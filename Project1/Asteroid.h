#pragma once

#include <random>
#include "Object.h"

class Asteroid: public Object
{
public:
    Asteroid();
    virtual ~Asteroid() override;

    virtual void init(SDL_Renderer* renderer) override;
    Vector2 isInsideWindow(Vector2 position, int window_width, int window_height);
    void update(float delta, int window_width, int window_height);
    static float randomFloat(float a, float b);
};
