#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

class Image
{
public:
    Image();
    ~Image();

    bool create_texture(const char* path, SDL_Renderer* renderer);
    void draw_texture(SDL_Renderer* renderer, const SDL_Rect& dest_rect);
    SDL_Texture* get_texture() const;
    int width() const { return m_width; }
    int height() const { return m_height; }

private:
    SDL_Surface* m_image = nullptr;
    SDL_Texture* m_texture = nullptr;
    int m_width;
    int m_height;
};
