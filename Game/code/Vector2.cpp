#include "Vector2.h"

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2::Vector2(int x, int y)
        : x(static_cast<float>(x)), y(static_cast<float>(y))
{
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

Vector2 operator*(const Vector2& v1, const Vector2& v2)
{
    return Vector2(v1.x * v2.x, v1.y * v2.y);
}

Vector2 operator*(const Vector2& v1, float value)
{
    return Vector2(v1.x * value, v1.y * value);
}

Vector2 operator*(float value, const Vector2& v1)
{
    return Vector2(v1.x * value, v1.y * value);
}

Vector2 operator/(const Vector2& v1, const Vector2& v2)
{
    return Vector2(v1.x / v2.x, v1.y / v2.y);
}

Vector2 operator/(const Vector2& v1, float value)
{
    return Vector2(v1.x / value, v1.y / value);
}

Vector2 Vector2::operator+=(const Vector2& v) { return *this + v; }

Vector2 Vector2::operator-=(const Vector2& v) { return *this - v; }

Vector2 Vector2::operator*=(const Vector2& v) { return *this * v; }

Vector2 Vector2::operator*=(float value) { return *this * value; }

Vector2 Vector2::operator/=(const Vector2& v) { return *this / v; }

Vector2 Vector2::operator/=(float value) { return *this / value; }

float Vector2::angle(const Vector2& v1,
                     const Vector2& v2) // Get angle  between two vectors
{
    const float PI_F = 3.14159265358979f;
    float cos_angle = dot(v1, v2) / (v1.lenght() * v2.lenght());
    float result = acos(cos_angle) * 180.0 / PI_F;
    return result;
}

Vector2 Vector2::normalized() const // Get normalized vector (lenght == 1)
{
    if (lenghtSquared() != 0)
    {
        return *this / lenght();
    }
    else
    {
        return *this;
    }
}

Vector2 Vector2::makeRotation(float angle)
{
    return Vector2(static_cast<float>(cos(angle)),
                   static_cast<float>(sin(angle)));
}

bool Vector2::isLeft(const Vector2& v) // Return true if *this vector is in the
                                       // left side of vector v
{
    Vector2 rot90(-(this->y), this->x); // This is vector *this which was
                                        // rotated to 90 degrees to the left.
    float dot_vect = dot(v, rot90);
    if (dot_vect < 0)
        return true;
    else
        return false;
}

// Get distance between two points
float Vector2::distance(const Vector2& pointA, const Vector2& pointB)
{
    float diff = (pointB.x - pointA.x) * (pointB.x - pointA.x) +
                 (pointB.y - pointA.y) * (pointB.y - pointA.y);
    return sqrt(diff);
}
