#include "Asteroid.h"

Asteroid::Asteroid()
{}

Asteroid::~Asteroid()
{
    m_image.reset();
}

void Asteroid::init(SDL_Renderer* renderer)
{
    const float  PI_F = 3.14159265358979f;
    const char* path = "assets/asteroid.png";
    m_image = std::make_unique<Image>();
    m_image->create_texture(path, renderer);
    m_radians = random_float(0.0, 2 * PI_F);
    m_active = true;
    float  a = random_float(0.0, 800.0);
    float  b = random_float(0.0, 600.0);
    m_position = Vector2(a, b);
    m_speed = 20;
    m_radius = radius();
}

float Asteroid::random_float(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

Vector2 Asteroid::is_inside_window(Vector2 position, int window_width, int window_height)
{
    Vector2 result;
    float max_x = window_width;
    if (position.x < -m_image->width())
        result.x = max_x;
    else if (position.x >= max_x)
        result.x = -m_image->width();
    else
        result.x = position.x;

    float max_y = window_height;

    if (position.y < -m_image->height())
        result.y = max_y;
    else if (position.y >= max_y)
        result.y = -m_image->height();
    else
        result.y = position.y;

    return result;
}

void Asteroid::update(float delta, int window_width, int window_height)
{
    Vector2 position;
    Vector2 turnvect = Vector2::make_rotation(m_radians);
    position = m_position + turnvect * m_speed * delta;

    position = is_inside_window(position, window_width, window_height);
    set_position(position);
}