#pragma once
#include "AsteroidManager.h"
#include "SmallAsteroid.h"

class SmallAsteroidManager : public Asteroidmanager
{
public:
    SmallAsteroidManager();
    virtual ~SmallAsteroidManager() override;

    void init(SDL_Renderer* renderer);
    std::unique_ptr<SmallAsteroid>& operator[] (const int index);
    void render(SDL_Renderer* renderer);
    void update(int window_width, int window_height, float delta);  
private:
    std::unique_ptr<SmallAsteroid> mAsteroid;
    std::array<std::unique_ptr<SmallAsteroid>, 30> mAsteroids;
};
