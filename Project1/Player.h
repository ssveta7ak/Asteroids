#pragma once

#include "Object.h"

class Player: public Object
{
public:
    Player();
    ~Player();
    
    virtual void init(SDL_Renderer* renderer) override;
    virtual void render(SDL_Renderer* renderer) override;
    Vector2 isInsideWindow( Vector2 position, int window_width, int window_height);
    void setAngle(float angle);
    void changeAngleTo(float delta_degrees);
    float degrees() const { return mDegrees; }
    float radians() { return mDegrees * M_PI / 180.0f; }
    void moveForward(float delta, int window_width, int window_height, int forward);
    float getAcceleration() { return mAcceleration; }
    void rotateToMouse(const Vector2& vec);
    void setRadMoving(float rad_moving) { mRadMoving = rad_moving; }

    void speedUp(float delta, int window_width, int window_height);
    void speedDown(float delta, int window_width, int window_height);

    bool isForward() const { return mIsForward; }
    void setForward(bool value) { mIsForward = value;}
   
private:
    bool mIsForward = true;
    float mDegrees = 0; //Angle of rotation
    float mRadMoving = 0;
    float mAcceleration = 3;
};
