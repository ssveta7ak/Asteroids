#include "Object.h"

Object::Object()
{}

Object::~Object()
{}

void Object::render(SDL_Renderer* renderer)
{
    SDL_Rect dest_rect;
    dest_rect.w = mImage->width();
    dest_rect.h = mImage->height();
    dest_rect.x = static_cast<int>(round(mPosition.x));
    dest_rect.y = static_cast<int>(round(mPosition.y));

    mImage->render(renderer, dest_rect);
}

bool Object::isInsideWindow(int window_width, int window_height)
{
    int max_x = window_width - mImage->width();
    int max_y = window_height - mImage->height();
    if (mPosition.x >= 0 && mPosition.x <= max_x && mPosition.y >= 0 && mPosition.y <= max_y)
        return true;
    else
        return false;
}

void Object::setPosition(const Vector2& position)
{
    mPosition.x = position.x;
    mPosition.y = position.y;
}

void Object::update(float delta)
{
    Vector2 position;
    Vector2 turnvect = Vector2::makeRotation(mRadians);
    position = mPosition + turnvect * mSpeed * delta;
    setPosition(position);
}

Vector2 Object::center() const
{
    Vector2 center;
    center.x = mPosition.x + mImage->width() / 2;
    center.y = mPosition.y + mImage->height() / 2;
    return center;
}

float Object::radius() const
{
    float w = static_cast<float>(mImage->width());
    float h = static_cast<float>(mImage->height());
    if (w > h)
        return h / 2.0;
    else
        return w / 2.0;
}

bool Object::iscrossed(const Object& A, const Object& B)
{
    float dist = Vector2::distance(A.center(), B.center());
    if (dist <= (A.mRadius + B.mRadius))
        return true;
    else
        return false;
}

void Object::reset()
{
    mActive = false;
    mPosition = Vector2(-100, -100);
}