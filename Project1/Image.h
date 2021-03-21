#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include <cassert> 
#include <windows.h>

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
    void render(SDL_Renderer* renderer, const SDL_Rect& dest_rect, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0, SDL_Point* center = NULL);


private:
    SDL_Surface* m_image = nullptr;
    SDL_Texture* m_texture = nullptr;

    //Image dimensions
    int m_width;
    int m_height;
};
