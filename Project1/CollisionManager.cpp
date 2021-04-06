#include "CollisionManager.h"


void CollisionManager::update( BulletManager& bullets, AsteroidManager& asteroids,
    AsteroidManager& smallAsteroids, Player& player)
{
    //check crossing bullet and asteroid
    for (int i = 0; i < bullets.size(); ++i)
    {
        if (bullets[i]->isActive())
        {
            for (int j = 0; j < asteroids.size(); ++j)
            {
                Object* obj1 = bullets[i].get();
                Object* obj2 = &asteroids[j];

                bool iscross = Object::iscrossed(*obj1, *obj2);
                if (iscross)
                {
                    if (!mAsteroidDestroyedListener.empty())
                    {
                        for (auto listener : mAsteroidDestroyedListener)
                        {
                            listener->onAsteroidDestroyed(asteroids[j]);
                        }
                    }
                    for (int k = 0; k < smallAsteroids.size(); ++k)
                    {
                        if (!smallAsteroids[k].isActive())
                        {
                            smallAsteroids[k].setActive(true);
                            smallAsteroids[k].setPosition(asteroids[j].position());
                            smallAsteroids.setActiveCount(smallAsteroids.activeCount() + 1);
                            for (int t = k; t < smallAsteroids.size(); ++t)
                            {
                                if (!smallAsteroids[t].isActive())
                                {
                                    smallAsteroids[t].setActive(true);
                                    smallAsteroids[t].setPosition(asteroids[j].position());
                                    smallAsteroids.setActiveCount(smallAsteroids.activeCount() + 1);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    asteroids.setActiveCount(asteroids.activeCount() - 1);
                    asteroids[j].reset(); //set default
                    bullets[i]->reset(); //set default
                    break;
                }
            }
        }

    }

    //check crossing bullet and small asteroid
    for (std::unique_ptr<Bullet>& bullet : bullets)
    {
        if (bullet->isActive())
        {
            for (Asteroid& smallAsteroid : smallAsteroids)
            {
                if (smallAsteroid.isActive())
                {
                    Object* obj1 = bullet.get();
                    Object* obj2 = &smallAsteroid;

                    bool iscross = Object::iscrossed(*obj1, *obj2);
                    if (iscross)
                    {
                        if (!mAsteroidDestroyedListener.empty())
                        {
                            for (auto listener : mAsteroidDestroyedListener)
                            {
                                listener->onAsteroidDestroyed(smallAsteroid);
                            }
                        }
                        smallAsteroids.setActiveCount(smallAsteroids.activeCount() - 1);
                        smallAsteroid.reset();
                        bullet->reset();
                        break;
                    }
                }
            }
        }
    }

    //check crossing player and asteroid
    for (Asteroid& asteroid : asteroids)
    {
        if (player.isActive())
        {
            Object* obj1 = &asteroid;
            Object* obj2 = &player;
            bool iscross = Object::iscrossed(*obj1, *obj2);
            if (iscross)
            {
                if (!mPlayerKilledListener.empty())
                {
                    for (auto listener : mPlayerKilledListener)
                    {
                        listener->onPlayerKilled(asteroid);
                    }
                }
                asteroids.setActiveCount(asteroids.activeCount() - 1);
                asteroid.reset(); //set default
                return;
            }
        }
    }

    //check crossing player and small asteroid
    for (Asteroid& smallAsteroid : smallAsteroids)
    {
        if (smallAsteroid.isActive() && player.isActive())
        {
            Object* obj1 = &smallAsteroid;
            Object* obj2 = &player;
            bool iscross = Object::iscrossed(*obj1, *obj2);
            if (iscross)
            {
                if (!mPlayerKilledListener.empty())
                {
                    for (auto listener : mPlayerKilledListener)
                    {
                        listener->onPlayerKilled(smallAsteroid);
                    }
                }
                smallAsteroids.setActiveCount(smallAsteroids.activeCount() - 1);
                smallAsteroid.reset(); //set default
                return;
            }
        }
    }
}

