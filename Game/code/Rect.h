#pragma once

#include "Vector2.h"

class Rect
{
public:
    Rect() {}
    Rect(float x, float y, float w, float h)
            : x(x), y(y), w(w), h(h)
    {}

    float x = 0.0f; // x, y - center of rectangle
    float y = 0.0f; 
    float w = 0.0f; // width of rectangle from center (x, y)
    float h = 0.0f; // height of rectangle from center (x, y)
    
    bool contains(const Vector2& point) const;
    bool intersects(const Rect& rect) const;
   
    
};