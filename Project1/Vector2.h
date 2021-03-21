#pragma once

#include <math.h> 
#include <numbers>

class Vector2
{
public:
    float x = 0;
    float y = 0;

    Vector2() = default;
    Vector2(float x, float y);
    Vector2(int x, int y);
    Vector2(const Vector2& vector) : x(vector.x), y(vector.y) {}

    Vector2 operator+=(const Vector2& v);
    Vector2 operator-=(const Vector2& v);
    Vector2 operator*=(const Vector2& v);
    Vector2 operator*=(float value);
    Vector2 operator/=(const Vector2& v);
    Vector2 operator/=(float value);

    float lenght() const { return sqrt(lenght_squared()); }
    float lenght_squared() const { return x * x + y * y; }
    Vector2 normalized() const;
    bool is_left(const Vector2& v);

    static Vector2 make_rotation(float angle);  // angle in radians
    static float dot(const Vector2& v1, const Vector2& v2) { return (v1.x * v2.x + v1.y * v2.y); }
    static float angle(const Vector2& v1, const Vector2& v2);
    static float distance(const Vector2& pointA, const Vector2& pointB);
};


Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);

Vector2 operator*(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v1, float value);
Vector2 operator*(float value, const Vector2& v1);

Vector2 operator/(const Vector2& v1, const Vector2& v2);
Vector2 operator/(const Vector2& v1, float value);