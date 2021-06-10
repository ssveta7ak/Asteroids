#include "BulletManager.h"
#include <algorithm>

void BulletManager::init(
        SDL_Renderer* renderer) // Create and initialize bullets
{
    for (std::unique_ptr<Bullet>& bullet : mBullets)
    {
        std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
        newBullet->init(renderer);
        bullet = std::move(newBullet);
    }
}

std::unique_ptr<Bullet>& BulletManager::operator[](const int index)
{
    return mBullets[index];
}

void BulletManager::render(SDL_Renderer* renderer) // Render active bullets
{
    for (std::unique_ptr<Bullet>& bullet : mBullets)
    {
        if (bullet->isActive())
        {
            bullet->render(renderer);
        }
    }
}

// Update position of active bullet. Set bullet as inactive when it goes outside
// the window.
void BulletManager::updateFireBullet(int windowWidth, int windowHeight,
                                     float delta)
{
    for (std::unique_ptr<Bullet>& bullet : mBullets)
    {
        if (!bullet->isActive())
        {
            continue;
        }
        bullet->update(delta);
        bool isInWindow = bullet->isInsideWindow(windowWidth, windowHeight);
        if (!isInWindow)
        {
            bullet->setActive(false);
            bullet->setPosition(Vector2(0, 0));
        }
    }
}

Bullet* BulletManager::spawnBullet()
{
    // Find the first inactive bullet in array
    auto it = std::find_if(mBullets.begin(), mBullets.end(),
                           [](const std::unique_ptr<Bullet>& bullet) -> bool {
                               return !bullet->isActive();
                           });

    if (it != mBullets.end())
    {
        Bullet* bullet = it->get();
        bullet->setActive(true); // Make active this bullet

        for (auto listener : mBulletSpawnListener)
        {
            listener->onBulletSpawn(); // Send event of bullet spawn for
                                       // listeners
        }

        return bullet;
    }

    return nullptr;
}
