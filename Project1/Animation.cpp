#include "Animation.h"

void Animation::init(SDL_Renderer *renderer)
{
    mAnimation = std::make_unique<Image>();
    if (mAnimation->createTexture("assets/textures/explosion.png", renderer))
    {
        int w = mAnimation->width();
        int h = mAnimation->height();
        // Set sprite clips
        mSpriteClips[0].x = 0;
        mSpriteClips[0].y = 0;
        mSpriteClips[0].w = w / 3;
        mSpriteClips[0].h = h;

        mSpriteClips[1].x = w / 3;
        mSpriteClips[1].y = 0;
        mSpriteClips[1].w = w / 3;
        mSpriteClips[1].h = h;

        mSpriteClips[2].x = 2 * w / 3;
        mSpriteClips[2].y = 0;
        mSpriteClips[2].w = w / 3;
        mSpriteClips[2].h = h;
    }
}

void Animation::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip)
{
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mAnimation->width(), mAnimation->height()};

    // Set clip rendering dimensions
    if (clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopy(renderer, mAnimation->getTexture(), clip, &renderQuad);
}

void Animation::setPosition(Vector2 pos)
{
    mPosition.x = pos.x;
    mPosition.y = pos.y;
}

void Animation::reset()
{
    isActive = false;
    mDuration = 240;
}