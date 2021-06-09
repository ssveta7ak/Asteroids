#include "Quadtree.h"

Quadtree::Quadtree(const Rect& boundary, int capacity) : mBoundary( boundary), mCapacity( capacity) {}

void Quadtree::subdivide()
{ 
    float x = mBoundary.x;
    float y = mBoundary.y;
    float w = mBoundary.w;
    float h = mBoundary.h;

    Rect ne = Rect(x + w / 2, y - h / 2, w / 2, h / 2);
    mNorthEast = std::make_unique<Quadtree>(ne, mCapacity);

    Rect nw = Rect(x - w / 2, y - h / 2, w / 2, h / 2);
    mNorthWest = std::make_unique<Quadtree>(nw, mCapacity);

    Rect se = Rect(x + w / 2, y + h / 2, w / 2, h / 2);
    mSouthEast = std::make_unique<Quadtree>(se, mCapacity);

    Rect sw = Rect(x - w / 2, y + h / 2, w / 2, h / 2);
    mSouthWest = std::make_unique<Quadtree>(sw, mCapacity);
    isDivided = true;
}

bool Quadtree::insert(Asteroid& obj)
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
        if (mNorthEast->insert(obj))
        {
            return true;
        }
        else if (mNorthWest->insert(obj))
        {
            return true;
        }
        else if (mSouthEast->insert(obj))
        {
            return true;
        }
        else if (mSouthWest->insert(obj))
        {
            return true;
        }
    }
}


std::vector<Asteroid*> Quadtree::query(const Rect& range)
{ 
    std::vector<Asteroid*> found;
    if (!mBoundary.intersects(range))
    {
        found.clear();
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
            std::vector<Asteroid*> ne = mNorthEast->query(range);
            std::vector<Asteroid*> nw = mNorthWest->query(range);
            std::vector<Asteroid*> se = mSouthEast->query(range);
            std::vector<Asteroid*> sw = mSouthWest->query(range);

            found.insert(found.end(), ne.begin(), ne.end());
            found.insert(found.end(), nw.begin(), nw.end());
            found.insert(found.end(), se.begin(), se.end());
            found.insert(found.end(), sw.begin(), sw.end());
        }
    }
    return found;
}

