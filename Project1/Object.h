#pragma once

#include "SDL.h"
#include "Vector2.h"
#include "Image.h"
#include <iostream>
#include <math.h>

class Object
{
public:
    Object();
    virtual ~Object();

    virtual void init(SDL_Renderer* renderer) = 0;
    virtual void render(SDL_Renderer* renderer);
    bool isInsideWindow(int window_width, int window_height);
    static bool iscrossed(const Object& A, const Object& B);
    virtual void update(float delta);
    Vector2 center()const;
    float radius() const;
    void reset();

    Vector2 position() const { return mPosition; }
    void setPosition(const Vector2& position);

    bool isActive() const { return mActive; }
    void setActive(bool active) { mActive = active; }

    float radians() const { return mRadians; }
    void setRadians(float radians) { mRadians = radians; }

    void setSpeed(float value) { mSpeed = value; }
    float getSpeed() const { return mSpeed; }

    int getWidth() const { return mImage->width(); }
    int getHeight() const { return mImage->height(); }

protected:
    std::unique_ptr<Image> mImage;
    Vector2 mPosition;
    bool mActive = false;
    float mRadians = 0;
    float mSpeed;
    float mRadius;
};