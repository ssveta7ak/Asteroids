#include "Image.h"

Image::Image()
{}

Image::~Image()
{
    if (mImage)
    {
        SDL_FreeSurface(mImage);
    }
    if (mTexture)
    {
        SDL_DestroyTexture(mTexture);
    }
}

bool Image::createTexture(const char* path, SDL_Renderer* renderer)
{
    mImage = IMG_Load(path);
    if (!mImage)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return false;
    }
    mTexture = SDL_CreateTextureFromSurface(renderer, mImage);
    if (!mTexture)
    {
        printf("CreateTextureFromSurface failed: %s\n", SDL_GetError());
        return false;
    }
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
    return true;
}

SDL_Texture* Image::getTexture() const
{
    return mTexture;
}

void Image::drawTexture(SDL_Renderer* renderer, const SDL_Rect& dest_rect)
{
    SDL_Rect src_rect;
    src_rect.w = mWidth;
    src_rect.h = mHeight;
    src_rect.x = 0;
    src_rect.y = 0;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, mTexture, &src_rect, &dest_rect);
    SDL_RenderPresent(renderer);
}

void Image::render(SDL_Renderer* renderer, const SDL_Rect& dest_rect, SDL_RendererFlip flip, double angle, SDL_Point* center)
{
    SDL_Rect src_rect;
    src_rect.w = mWidth;
    src_rect.h = mHeight;
    src_rect.x = 0;
    src_rect.y = 0;

    //Render to screen
    int res = SDL_RenderCopyEx(renderer, mTexture, &src_rect, &dest_rect, angle, center, flip);
}

bool Image::createFromRenderedText(std::string textureText, SDL_Color textColor, int textSize, SDL_Renderer* renderer)
{
    //Globally used font
    TTF_Font* gFont = TTF_OpenFont("assets/Lexend/Lexend-SemiBold.ttf", textSize);
    if (!gFont)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    else
    {
        mImage = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
        if (!mImage)
        {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
            return false;
        }
        else
        {
            //Create texture from surface pixels
            mTexture = SDL_CreateTextureFromSurface(renderer, mImage);
            if (!mTexture)
            {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
                return false;
            }
            else
            {
                SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
            }
        }
        
    }
    return mTexture != NULL;
}
