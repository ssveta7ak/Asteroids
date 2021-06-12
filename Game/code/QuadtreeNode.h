#pragma once

#include "Rect.h"
#include "Asteroid.h"
#include <vector>
#include <array>
#include <memory>

class QuadtreeNode
{
public:
    QuadtreeNode(const Rect& boundary, int capacity);

    bool insert(Asteroid& obj);
    void subdivide();
    void query(const Rect& range, std::vector<Asteroid*>& found);

private:
    Rect mBoundary;
    int mCapacity;
    bool isDivided = false;
    std::vector<Asteroid*> points;
    std::array<std::unique_ptr<QuadtreeNode>, 4> mChildren;
};
