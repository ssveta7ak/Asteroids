#include "BulletManager.h"

BulletManager::BulletManager()
{}

BulletManager::~BulletManager()
{}

void BulletManager::init(SDL_Renderer* renderer)
{
    for (int i = 0; i < mBullets.size(); ++i)
    {
        mBullet = std::make_unique<Bullet>();
        mBullet->init(renderer);
        mBullets.at(i) = std::move(mBullet);
    }
}

std::unique_ptr<Bullet>& BulletManager::operator[] (const int index)
{
    return mBullets[index];
}

void BulletManager::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < mBullets.size(); ++i)
    {
        if (mBullets[i]->isActive())
        {
            mBullets[i]->render(renderer);
        }
    }
}

void BulletManager::updateFireBullet(int window_width, int window_height, float delta)
{
    for (auto& bullet : mBullets)
    {
        if (bullet->isActive())
        {
            bullet->update(delta);
            bool isInWindow = bullet->isInsideWindow(window_width, window_height);
            if (!isInWindow)
            {
                bullet->setActive(false);
                bullet->setPosition(Vector2(0, 0));
            }
        }
    }
}
