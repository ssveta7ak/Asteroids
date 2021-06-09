#pragma once

#include "Object.h"

class Asteroid : public Object
{
public:
    bool isbig() const { return isBig; }
    void init(SDL_Renderer* renderer, bool big, int width, int height);
    virtual void init(SDL_Renderer* renderer) override;
    Vector2 isInsideWindow(Vector2 position, int windowWidth, int windowHeight);
    void update(float delta, int windowWidth, int windowHeight);

private:
    bool isBig;
};
