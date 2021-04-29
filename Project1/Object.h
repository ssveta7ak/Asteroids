#pragma once

#include "Image.h"
#include "Vector2.h"
#include <memory>

#define DEGREES_FROM_RADIANS(x) (x) * 180.0f / M_PI
#define RADIANS_FROM_DEGREES(x) (x) * M_PI / 180.0f

class Object
{
public:
    Object() = default;

    Object(const Object &rhs) = delete;
    Object &operator=(const Object &rhs) = delete;

    Object(Object &&rhs) = default;
    Object &operator=(Object &&rhs) = default;

    virtual ~Object() = default;

    virtual void init(SDL_Renderer *renderer) = 0;
    virtual void render(SDL_Renderer *renderer) const;
    virtual void update(float delta);

    static float randomFloat(float a, float b);
    static bool iscrossed(const Object &A, const Object &B);

    bool isInsideWindow(int windowWidth, int windowHeight);
    float radius() const;
    void reset();
    Vector2 center() const;

    Vector2 position() const { return mPosition; }
    void setPosition(Vector2 position);

    bool isActive() const { return mActive; }
    void setActive(bool active) { mActive = active; }

    float angle() const { return mAngle; }         // return angle in radians
    void setAngle(float angle) { mAngle = angle; } // set angle in radians

    void setSpeed(float value);
    float getSpeed() const { return mSpeed; }

    int width() const { return mImage->width(); }
    int height() const { return mImage->height(); }

protected:
    std::unique_ptr<Image> mImage;
    Vector2 mPosition;
    float mAngle = 0; // angle in radians
    float mSpeed = 1;
    float mRadius = 1;
    bool mActive = false;
};