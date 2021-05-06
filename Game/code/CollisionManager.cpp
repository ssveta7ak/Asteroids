#include "CollisionManager.h"

void CollisionManager::update(BulletManager& bullets,
                              AsteroidManager& asteroids,
                              AsteroidManager& smallAsteroids, Player& player)
{
    // check crossing bullet and asteroid
    for (int i = 0; i < bullets.size(); ++i)
    {
        if (bullets[i]->isActive())
        {
            for (int j = 0; j < asteroids.size(); ++j)
            {
                Object* obj1 = bullets[i].get();
                Object* obj2 = &asteroids[j];

                // Check collision of two objects
                bool iscross = Object::iscrossed(*obj1, *obj2);
                if (iscross)
                {
                    for (auto listener : mAsteroidDestroyedListener)
                    {
                        // Send event of asteroid destroying for listeners
                        listener->onAsteroidDestroyed(asteroids[j]);
                    }

                    // Create two small asteroids after destroying big asteroid
                    for (int k = 0; k < smallAsteroids.size(); ++k)
                    {
                        if (!smallAsteroids[k].isActive())
                        {
                            smallAsteroids[k].setActive(true);
                            smallAsteroids[k].setPosition(
                                    asteroids[j].position());
                            ++smallAsteroids;
                            for (int t = k; t < smallAsteroids.size(); ++t)
                            {
                                if (!smallAsteroids[t].isActive())
                                {
                                    smallAsteroids[t].setActive(true);
                                    smallAsteroids[t].setPosition(
                                            asteroids[j].position());
                                    ++smallAsteroids;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    // Decrease count of active big asteroids
                    --asteroids;
                    asteroids[j].reset(); // Set default properties
                    bullets[i]->reset();  // Set default properties
                    break;
                }
            }
        }
    }

    // check crossing bullet and small asteroid
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
                        for (auto listener : mAsteroidDestroyedListener)
                        {
                            // Send event of asteroid destroying for listeners
                            listener->onAsteroidDestroyed(smallAsteroid);
                        }

                        // Decrease count of active small asteroids
                        --smallAsteroids;
                        smallAsteroid.reset(); // Set default properties
                        bullet->reset();       // Set default properties
                        break;
                    }
                }
            }
        }
    }

    // check crossing player and asteroid
    for (Asteroid& asteroid : asteroids)
    {
        if (player.isActive())
        {
            Object* obj1 = &asteroid;
            Object* obj2 = &player;
            bool iscross = Object::iscrossed(*obj1, *obj2);
            if (iscross)
            {
                for (auto listener : mPlayerKilledListener)
                {
                    // Send event of player killing for listeners
                    listener->onPlayerKilled(asteroid);
                }

                // Decrease count of active big asteroids
                --asteroids;
                asteroid.reset(); // Set default properties
                return;
            }
        }
    }

    // check crossing player and small asteroid
    for (Asteroid& smallAsteroid : smallAsteroids)
    {
        if (smallAsteroid.isActive() && player.isActive())
        {
            Object* obj1 = &smallAsteroid;
            Object* obj2 = &player;
            bool iscross = Object::iscrossed(*obj1, *obj2);
            if (iscross)
            {
                for (auto listener : mPlayerKilledListener)
                {
                    // Send event of player killing for listeners
                    listener->onPlayerKilled(smallAsteroid);
                }

                // Decrease count of active small asteroids
                --smallAsteroids;
                smallAsteroid.reset(); // Set default properties
                return;
            }
        }
    }
}
