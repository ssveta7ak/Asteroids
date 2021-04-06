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

void Player::render(SDL_Renderer* renderer) const
{
    SDL_Rect dest_rect;
    dest_rect.w = mImage->width();
    dest_rect.h = mImage->height();
    dest_rect.x = static_cast<int>(round(mPosition.x));
    dest_rect.y = static_cast<int>(round(mPosition.y));
    
    if (mActive)
    {
        mImage->render(renderer, dest_rect, SDL_FLIP_NONE, DEGREES_FROM_RADIANS(mAngle));
    }
}



void Player::changeAngleTo(float deltaDegrees)
{
    setAngle(mAngle + RADIANS_FROM_DEGREES(deltaDegrees));
    if (mAngle >= 2 * M_PI)
    {
        setAngle(mAngle - 2 * M_PI);
    }
    if (mAngle < 0.0)
    {
        setAngle(2 * M_PI);
    }
}

void Player::moveForward(float delta, int windowWidth, int windowHeight, int forward )
{
    Vector2 turnvect;
    Vector2 b;
    Vector2 movePosition;
    turnvect = Vector2::makeRotation(mAngleMoving);

  /*  b.x = -turnvect.y * mPosition.y / turnvect.x;
    b.y = mPosition.y;
    b = b.normalized();*/

    switch (forward)
    {
    case 1:
        movePosition = mPosition + turnvect * mSpeed * delta;
        break;
    case 2:
        movePosition = mPosition - turnvect * mSpeed * delta;
        break;
    case 3:
      //  movePosition = mPosition - b * mSpeed * delta;
        break;
    case 4:
     //   movePosition = mPosition + b * mSpeed * delta;
        break;
    }

    movePosition = isInsideWindow(movePosition, windowWidth, windowHeight);
    setPosition(movePosition);
}

void Player::goRight(float delta, int windowWidth, int windowHeight)
{
    setSpeed(mSpeed + mAcceleration);
    setForward(true);
    mAngleMoving = mAngle;
    moveForward(delta, windowWidth, windowHeight, 4);
}

void Player::goLeft(float delta, int windowWidth, int windowHeight)
{
    setSpeed(mSpeed + mAcceleration);
    setForward(true);
    mAngleMoving = mAngle;
    moveForward(delta, windowWidth, windowHeight, 3);
}

void Player::speedUp(float delta, int windowWidth, int windowHeight)
{
    setSpeed(mSpeed + mAcceleration);
    setForward(true);
    mAngleMoving = mAngle;;
    moveForward(delta, windowWidth, windowHeight, 1);
}

void Player::speedDown(float delta, int windowWidth, int windowHeight)
{
    if (mIsForward)
    {
        setSpeed(mSpeed - mAcceleration);
        mAngleMoving = mAngle;
        moveForward(delta, windowWidth, windowHeight, 1);
    }
    if (mSpeed <= 100)
    {
        setForward(false);
        mAngleMoving = mAngle;
        moveForward(delta, windowWidth, windowHeight, 2);
    }
}

Vector2 Player::isInsideWindow(Vector2 position, int windowWidth, int windowHeight)
{
    Vector2 result;
    float maxX = windowWidth - mImage->width();
    if (position.x < 0)
        result.x = maxX;
    else if (position.x >= maxX)
        result.x = 0;
    else
        result.x = position.x;

    float maxY = windowHeight - mImage->height();

    if (position.y < 0)
        result.y = maxY;
    else if (position.y >= maxY)
        result.y = 0;
    else
        result.y = position.y;
    
    return result;
}

void Player::rotateToMouse(Vector2 point)
{
    Vector2 mouse;
    mouse = point - center();
    mouse = mouse.normalized();
    Vector2 directPos = Vector2::makeRotation(mAngle);

    float angle = Vector2::angle(directPos, mouse);

    bool res = mouse.isLeft(directPos);
    if (res)
    {
        changeAngleTo(angle);
    }
    else
    {
        changeAngleTo(-angle);
    }
}
