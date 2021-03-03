#include "Image.h"

Image::Image()
{}

Image::~Image()
{
    if (m_image)
    {
        SDL_FreeSurface(m_image);
    }
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture); 
    }
}

bool Image::create_texture(const char* path, SDL_Renderer* renderer)
{
    m_image = IMG_Load(path);
    if (!m_image)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return false;
    }
    m_texture = SDL_CreateTextureFromSurface(renderer, m_image);
    if (!m_texture)
    {
        printf("CreateTextureFromSurface failed: %s\n", SDL_GetError());
        return false;
    }
    SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);
    return true;
}

SDL_Texture* Image::get_texture() const
{
    return m_texture;
}

void Image::draw_texture(SDL_Renderer* renderer, const SDL_Rect& dest_rect)
{
    SDL_Rect src_rect;
    src_rect.w = m_width;
    src_rect.h = m_height;
    src_rect.x = 0;
    src_rect.y = 0;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, m_texture, &src_rect, &dest_rect);
    SDL_RenderPresent(renderer);
}

