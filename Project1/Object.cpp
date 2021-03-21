#include "Object.h"

Object::Object()
{
}

Object::~Object()
{}

void Object::render(SDL_Renderer* renderer)
{
    SDL_Rect dest_rect;
    dest_rect.w = m_image->width();
    dest_rect.h = m_image->height();
    dest_rect.x = static_cast<int>(round(m_position.x));
    dest_rect.y = static_cast<int>(round(m_position.y));

    m_image->render(renderer, dest_rect);
}

bool Object::is_inside_window(int window_width, int window_height)
{
    int max_x = window_width - m_image->width();
    int max_y = window_height - m_image->height();
    if (m_position.x >= 0 && m_position.x <= max_x && m_position.y >= 0 && m_position.y <= max_y)
        return true;
    else
        return false;
}

void Object::set_position(const Vector2& position)
{
    m_position.x = position.x;
    m_position.y = position.y;
}

void Object::update(float delta)
{
    Vector2 position;
    Vector2 turnvect = Vector2::make_rotation(m_radians);
    position = m_position + turnvect * m_speed * delta;
    set_position(position);
}

Vector2 Object::center()
{
    Vector2 center;
    center.x = m_position.x + m_image->width() / 2;
    center.y = m_position.y + m_image->height() / 2;
    return center;
}

float Object::radius()
{
    float w = static_cast<float>(m_image->width());
    float h = static_cast<float>(m_image->height());
    if (w > h)
        return h / 2.0;
    else
        return w / 2.0;
}

bool Object::iscrossed(const Object& A, const Object& B)
{
    float dist = Vector2::distance(A.m_position, B.m_position);
    if (dist <= (A.m_radius + B.m_radius))
        return true;
    else
        return false;
}