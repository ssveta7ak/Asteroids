#include "Asteroid.h"

Asteroid::Asteroid()
{}

Asteroid::~Asteroid()
{
    mImage.reset();
}

void Asteroid::init(SDL_Renderer* renderer)

{
    const char* path = "assets/asteroid.png";
    mImage = std::make_unique<Image>();
    mImage->createTexture(path, renderer);
    mRadians = randomFloat(0.0, 2 * M_PI);
    mActive = true; 
    float  a = randomFloat(0.0, 800.0);
    float  b = randomFloat(0.0, 600.0);
    mPosition = Vector2(a, b);
    mSpeed = 20;
    mRadius = radius();
}

float Asteroid::randomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

Vector2 Asteroid::isInsideWindow(Vector2 position, int window_width, int window_height)
{
    Vector2 result;
    float max_x = window_width;
    if (position.x < -mImage->width())
        result.x = max_x;
    else if (position.x >= max_x)
        result.x = -mImage->width();
    else
        result.x = position.x;

    float max_y = window_height;

    if (position.y < -mImage->height())
        result.y = max_y;
    else if (position.y >= max_y)
        result.y = -mImage->height();
    else
        result.y = position.y;

    return result;
}

void Asteroid::update(float delta, int window_width, int window_height)
{
    Vector2 position;
    Vector2 turnvect = Vector2::makeRotation(mRadians);
    position = mPosition + turnvect * mSpeed * delta;

    position = isInsideWindow(position, window_width, window_height);
    setPosition(position);
}