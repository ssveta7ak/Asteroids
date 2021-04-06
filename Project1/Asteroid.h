#pragma once

#include "Object.h"

class Asteroid : public Object
{
public:
    Asteroid() = default;

    Asteroid(const Asteroid& rhs) = delete;
    Asteroid& operator=(const Asteroid& rhs) = delete;

    Asteroid(Asteroid&& rhs) = default;
    Asteroid& operator=(Asteroid&& rhs) = default;

    virtual ~Asteroid() override;

    void init(SDL_Renderer* renderer, bool big, int width, int height);
    virtual void init(SDL_Renderer* renderer) override;
    Vector2 isInsideWindow(Vector2 position, int windowWidth, int windowHeight);
    void update(float delta, int windowWidth, int windowHeight);
};
