#include "QuadtreeNode.h"

QuadtreeNode::QuadtreeNode(const Rect& boundary, int capacity)
        : mBoundary(boundary), mCapacity(capacity)
{
}

void QuadtreeNode::subdivide()
{
    float x = mBoundary.x;
    float y = mBoundary.y;
    float w = mBoundary.w;
    float h = mBoundary.h;

    Rect ne = Rect(x + w / 2, y - h / 2, w / 2, h / 2);
    Rect nw = Rect(x - w / 2, y - h / 2, w / 2, h / 2);
    Rect se = Rect(x + w / 2, y + h / 2, w / 2, h / 2);
    Rect sw = Rect(x - w / 2, y + h / 2, w / 2, h / 2);

    mChildren[0] = std::make_unique<QuadtreeNode>(ne, mCapacity);
    mChildren[1] = std::make_unique<QuadtreeNode>(nw, mCapacity);
    mChildren[2] = std::make_unique<QuadtreeNode>(se, mCapacity);
    mChildren[3] = std::make_unique<QuadtreeNode>(sw, mCapacity);
    isDivided = true;
}


bool QuadtreeNode::insert(Asteroid& obj)
{
    if (!mBoundary.contains(obj.center()))
    {
        return false;
    }
    if (points.size() < mCapacity)
    {
        points.push_back(&obj);
        return true;
    }
    else
    {
        if (!isDivided)
        {
            subdivide();
        }
        for (auto& child : mChildren)
        {
            if (child->insert(obj))
            {
                return true;
            }
        }
    }
}


void QuadtreeNode::query(const Rect& range, std::vector<Asteroid*>& found)
{
    if (!mBoundary.intersects(range))
    {
        return;
    }
    else
    {
        for (auto object : points)
        {
            if (range.contains(object->center()))
            {
                found.push_back(object);
            }
        }
        if (isDivided)
        {
            for (auto& child : mChildren)
            {
                child->query(range, found);
            }
        }
    }
}
