#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Image.h"
#include <array>
#include "Vector2.h"
#include <iostream>

class Animation
{
public:
    Animation();
    ~Animation();

    void init(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);
    void reset();

    Vector2 position() const { return mPosition; }
    void setPosition(Vector2 position);

    static constexpr int ANIMATION_FRAMES = 3;
    SDL_Rect mSpriteClips[ANIMATION_FRAMES];
    bool isActive = false;
    int mDuration = 240;

private:
    std::unique_ptr<Image> mAnimation;
    Vector2 mPosition;
};