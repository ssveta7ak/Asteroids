#include "Player.h"

Player::Player()
{}

Player::~Player()
{
    mImage.reset();
}

void Player::init(SDL_Renderer* renderer)
{
    const char* path = "assets/ship.png";
    mImage = std::make_unique<Image>();
    mImage->createTexture(path, renderer);
    mSpeed = 1;
    mRadius = radius()/2;
    mActive = true;
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_Rect dest_rect;
    dest_rect.w = mImage->width();
    dest_rect.h = mImage->height();
    dest_rect.x = static_cast<int>(round(mPosition.x));
    dest_rect.y = static_cast<int>(round(mPosition.y));
    
    if (mActive)
    {
        mImage->render(renderer, dest_rect, SDL_FLIP_NONE, mDegrees);
    }
}

void Player::setAngle(float angle)
{
    mDegrees = angle;
}

void Player::changeAngleTo(float delta_degrees)
{
    setAngle(mDegrees + delta_degrees);
    if (mDegrees > 359.0f)
    {
        setAngle(mDegrees - 360.0);
    }
    if (mDegrees < 0.0)
    {
        setAngle(360.0);
    }
}

void Player::moveForward(float delta, int window_width, int window_height, int forward )
{
    Vector2 turnvect;
    //Vector2 b;
    Vector2 move_position;
    turnvect = Vector2::makeRotation(mRadMoving);

   /* b.x = -turnvect.y * m_position.y / turnvect.x;
    b.y = m_position.y;
    b = b.normalized();*/

    switch (forward)
    {
    case 1:
        move_position = mPosition + turnvect * mSpeed * delta;
        break;
    case 2:
        move_position = mPosition - turnvect * mSpeed * delta;
        break;
    case 3:
      //  move_position = m_position - b * SPEED * delta;
        break;
    case 4:
    //    move_position = m_position + b * SPEED * delta;
        break;
    }

    move_position = isInsideWindow(move_position, window_width, window_height);
    setPosition(move_position);
}

void Player::speedUp(float delta, int window_width, int window_height)
{
    setSpeed(mSpeed + mAcceleration);
    setForward(true);
    mRadMoving = radians();
    moveForward(delta, window_width, window_height, 1);
}

void Player::speedDown(float delta, int window_width, int window_height)
{
    if (mIsForward)
    {
        setSpeed(mSpeed - mAcceleration);
        mRadMoving = radians();
        moveForward(delta, window_width, window_height, 1);
    }
    if (mSpeed <= 100)
    {
        setForward(false);
        mRadMoving = radians();
        moveForward(delta, window_width, window_height, 2);
    }
}

Vector2 Player::isInsideWindow(Vector2 position, int window_width, int window_height)
{
    Vector2 result;
    float max_x = window_width - mImage->width();
    if (position.x < 0)
        result.x = max_x;
    else if (position.x >= max_x)
        result.x = 0;
    else
        result.x = position.x;

    float max_y = window_height - mImage->height();

    if (position.y < 0)
        result.y = max_y;
    else if (position.y >= max_y)
        result.y = 0;
    else
        result.y = position.y;
    
    return result;
}

void Player::rotateToMouse(const Vector2& point)
{
    Vector2 mouse;
    mouse = point - center();
    mouse = mouse.normalized();
    Vector2 direct_pos = Vector2::makeRotation(radians());

    float ang = Vector2::angle(direct_pos, mouse);

    bool res = mouse.isLeft(direct_pos);
    if (res)
    {
        changeAngleTo(ang);
    }
    else
    {
        changeAngleTo(-ang);
    }
}
