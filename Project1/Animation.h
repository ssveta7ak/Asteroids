#pragma once

#include "Image.h"
#include "Vector2.h"
#include <array>
#include <iostream>

class Animation
{
public:
    void init(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr);
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