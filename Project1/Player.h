#pragma once

#include "Object.h"

class Player : public Object
{
public:
    virtual void init(SDL_Renderer *renderer) override;
    virtual void render(SDL_Renderer *renderer) const override;
    Vector2 isInsideWindow(Vector2 position, int windowWidth, int windowHeight);
    void changeAngleTo(float deltaDegrees);
    void moveForward(float delta, int windowWidth, int windowHeight,
                     int forward);
    float getAcceleration() const { return mAcceleration; }
    void rotateToMouse(Vector2 vec);
    void setAngleMoving(float angleMoving)
    {
        mAngleMoving = angleMoving;
    } // angle in radians

    void speedUp(float delta, int windowWidth, int windowHeight);
    void speedDown(float delta, int windowWidth, int windowHeight);

    bool isForward() const { return mIsForward; }
    void setForward(bool value) { mIsForward = value; }

private:
    bool mIsForward = true;
    float mAngleMoving = 0;
    float mAcceleration = 2;
};
