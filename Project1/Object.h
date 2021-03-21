#pragma once

#include "SDL.h"
#include "Vector2.h"
#include "Image.h"
#include <iostream>

class Object
{
public:
    Object();
    virtual ~Object();

    virtual void init(SDL_Renderer* renderer) = 0;
    virtual void render(SDL_Renderer* renderer);
    bool is_inside_window(int window_width, int window_height);
    Vector2 position() { return m_position; }
    void set_position(const Vector2& position);
    bool is_active() const { return m_active; }
    void set_active(bool active) { m_active = active; }
    float radians() const { return m_radians; }
    void set_radians(float radians) { m_radians = radians; }
    virtual void update(float delta);
    Vector2 center();
    float radius();
    void set_speed(float value) { m_speed = value; }
    float get_speed() const { return m_speed; }
    int get_width() const { return m_image->width(); }
    int get_height() const { return m_image->height(); }
    static bool iscrossed(const Object& A, const Object& B);

protected:
    std::unique_ptr<Image> m_image;
    Vector2 m_position;
    bool m_active = false;
    float m_radians;
    float m_speed;
    float m_radius;
};