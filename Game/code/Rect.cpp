#include "Rect.h"

bool Rect::contains(const Vector2& point) const 
{
    return (point.x >= x - w && point.x <= x + w && point.y <= y + h &&
            point.y >= y - h);
}

bool Rect::intersects(const Rect& rect) const
{
    return !(rect.x - rect.w > x + w || rect.x + rect.w < x - w ||
            rect.y - rect.h > y + h || rect.y + rect.h < y - h);
}