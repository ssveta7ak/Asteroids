#include "Asteroid.h"

void Asteroid::init(SDL_Renderer* renderer, bool big, int width, int height)
{
    const char* path = "assets/textures/asteroid.png";
    const char* path2 = "assets/textures/small_asteroid.png";
    mImage = std::make_unique<Image>();
    if (big)
    {
        // Initialize big asteroids
        mImage->createTexture(path, renderer);
        mActive = true;
        mSpeed = 20;
        float a = randomFloat(0.0, width);
        float b = randomFloat(0.0, height);
        mPosition = Vector2(a, b);
    }
    else
    {
        // Initialize small asteroids
        mImage->createTexture(path2, renderer);
        mActive = false;
        mSpeed = 40;
        mPosition = Vector2(-50, -50);
    }
    isBig = big;
    mAngle = randomFloat(0.0, 2 * M_PI);
    mRadius = radius();
}

// Check and return position inside the window
// If object goes outside the window it appears in opposide window side
Vector2 Asteroid::isInsideWindow(Vector2 position, int windowWidth,
                                 int windowHeight)
{
    Vector2 result;
    float max_x = windowWidth;
    if (position.x < -mImage->width())
        result.x = max_x;
    else if (position.x >= max_x)
        result.x = -mImage->width();
    else
        result.x = position.x;

    float max_y = windowHeight;

    if (position.y < -mImage->height())
        result.y = max_y;
    else if (position.y >= max_y)
        result.y = -mImage->height();
    else
        result.y = position.y;

    return result;
}

// Update asteroid position
void Asteroid::update(float delta, int windowWidth, int windowHeight)
{
    Vector2 position;
    Vector2 turnvect = Vector2::makeRotation(mAngle);
    position = mPosition + turnvect * mSpeed * delta;

    position = isInsideWindow(position, windowWidth, windowHeight);
    setPosition(position);
}
void Asteroid::init(SDL_Renderer* renderer) {}