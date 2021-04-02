#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <string>
#include <cassert> 
#include <windows.h>

class Image
{
public:
    Image();
    ~Image();

    int width() const { return mWidth; }
    int height() const { return mHeight; }
    bool createTexture(const char* path, SDL_Renderer* renderer);
    void drawTexture(SDL_Renderer* renderer, const SDL_Rect& dest_rect);
    SDL_Texture* getTexture() const;
    void render(SDL_Renderer* renderer, const SDL_Rect& dest_rect, SDL_RendererFlip flip = SDL_FLIP_NONE,
                double angle = 0.0, SDL_Point* center = NULL);
    //Creates image from font string
    bool createFromRenderedText(std::string textureText, SDL_Color textColor, int textSize, SDL_Renderer* renderer);

private:
    SDL_Surface* mImage = nullptr;
    SDL_Texture* mTexture = nullptr;

    //Image dimensions
    int mWidth;
    int mHeight;
};
