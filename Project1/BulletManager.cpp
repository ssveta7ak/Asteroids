#include "BulletManager.h"
#include <algorithm> 

void BulletManager::init(SDL_Renderer* renderer)
{
    for (std::unique_ptr<Bullet>& bullet : mBullets)
    {
        std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
        newBullet->init(renderer);
        bullet = std::move(newBullet);
    }
}

std::unique_ptr<Bullet>& BulletManager::operator[] (const int index)
{
    return mBullets[index];
}

void BulletManager::render(SDL_Renderer* renderer)
{
    for (std::unique_ptr<Bullet>& bullet : mBullets)
    {
        if (bullet->isActive())
        {
            bullet->render(renderer);
        }
    }
}

void BulletManager::updateFireBullet(int windowWidth, int windowHeight, float delta)
{
    for (std::unique_ptr<Bullet>& bullet : mBullets)
    {
        if (bullet->isActive())
        {
            bullet->update(delta);
            bool isInWindow = bullet->isInsideWindow(windowWidth, windowHeight);
            if (!isInWindow)
            {
                bullet->setActive(false);
                bullet->setPosition(Vector2(0, 0));
            }
        }
    }
}

Bullet* BulletManager::spawnBullet()
{
    auto it = std::find_if(mBullets.begin(), mBullets.end(),
        [](const std::unique_ptr<Bullet>& bullet) -> bool
        {
            return !bullet->isActive();
        }
    );

    if (it != mBullets.end())
    {
        Bullet* bullet = it->get();
        bullet->setActive(true);

        if (!mBulletSpawnListener.empty())
        {
            for (auto listener : mBulletSpawnListener)
            {
                listener->onBulletSpawn();
            }
        }

        return bullet;
    }
    
    return nullptr;
}
