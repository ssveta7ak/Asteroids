#include "Object.h"

void Object::render(SDL_Renderer* renderer) const
{
    SDL_Rect dest_rect;
    dest_rect.w = mImage->width();
    dest_rect.h = mImage->height();
    dest_rect.x = static_cast<int>(round(mPosition.x));
    dest_rect.y = static_cast<int>(round(mPosition.y));

    mImage->render(renderer, dest_rect);
}

// Check object position inside the window
bool Object::isInsideWindow(int windowWidth, int windowHeight)
{
    int max_x = windowWidth - mImage->width();
    int max_y = windowHeight - mImage->height();
    if (mPosition.x >= 0 && mPosition.x <= max_x && mPosition.y >= 0 &&
        mPosition.y <= max_y)
        return true;
    else
        return false;
}

void Object::setPosition(Vector2 position)
{
    mPosition.x = position.x;
    mPosition.y = position.y;
}

// Update object position
void Object::update(float delta)
{
    Vector2 position;
    Vector2 turnvect = Vector2::makeRotation(mAngle);
    position = mPosition + turnvect * mSpeed * delta;
    setPosition(position);
}

Vector2 Object::center() const // Get object center position
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

// Check collision of two objects.
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

// Get random float between (a, b)
float Object::randomFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void Object::setSpeed(float value)
{
    const float MAX_SPEED = 150;
    mSpeed = (value < MAX_SPEED) ? value : MAX_SPEED;
}