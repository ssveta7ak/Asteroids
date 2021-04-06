#include "SoundManager.h"

SoundManager::~SoundManager()
{
    Mix_FreeMusic(mShot);
    Mix_FreeMusic(mExplosion);
}

bool SoundManager::init()
{
    bool success = true;
    //Load sound effects
    mShot = Mix_LoadMUS("assets/sound/shot.wav");
    if (!mShot)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    mExplosion = Mix_LoadMUS("assets/sound/explosion.wav");
    if (!mExplosion)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}
