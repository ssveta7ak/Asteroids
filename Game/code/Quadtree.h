#pragma once

#include "Rect.h"
#include "Asteroid.h"
#include <vector>
#include <array>
#include <memory>

class Quadtree
{
public:
    Quadtree(const Rect& boundary, int capacity);

    bool insert( Asteroid& obj);
    void subdivide();
    std::vector<Asteroid*> query(const Rect& range);

private:
    Rect mBoundary;
    int mCapacity;
    bool isDivided = false;
   // std::vector<Vector2> points;
    std::vector<Asteroid*> points;

    std::unique_ptr<Quadtree> mNorthEast;
    std::unique_ptr<Quadtree> mNorthWest;
    std::unique_ptr<Quadtree> mSouthEast;
    std::unique_ptr<Quadtree> mSouthWest;
};
