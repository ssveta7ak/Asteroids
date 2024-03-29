#include "AnimationManager.h"
#include "Asteroid.h"

void AnimationManager::init(SDL_Renderer* renderer)
{
    mRenderer = renderer;
    mAnimation.init(mRenderer);
}

// Activate animation when player was destroyed
void AnimationManager::onPlayerKilled(const Asteroid& asteroid)
{
    mAnimation.isActive = true;
    mAnimation.setPosition(asteroid.position());
}

// Activate animation when asteroid was destroed
void AnimationManager::onAsteroidDestroyed(const Asteroid& asteroid)
{
    mAnimation.isActive = true;
    mAnimation.setPosition(asteroid.position());
}

void AnimationManager::animate()
{
    if (mAnimation.isActive && mAnimation.mDuration > 0)
    {
        // Render current frame
        SDL_Rect* currentClip = &mAnimation.mSpriteClips[frame / 3];
        mAnimation.render(mRenderer, mAnimation.position().x,
                          mAnimation.position().y, currentClip);
        ++frame;

        // Cycle animation
        if (frame / 3 >= mAnimation.ANIMATION_FRAMES)
        {
            frame = 0;
        }
        --mAnimation.mDuration;
    }
    else if (mAnimation.mDuration <= 0)
    {
        mAnimation.reset();
    }
}
