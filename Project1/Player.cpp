#include "Player.h"

Player::Player()
{}

Player::~Player()
{
    m_image.reset();
}

void Player::init(SDL_Renderer* renderer)
{
    const char* path = "assets/ship.png";
    m_image = std::make_unique<Image>();
    m_image->create_texture(path, renderer);
    m_speed = 1;
    m_radius = radius()/2;
    m_active = true;
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_Rect dest_rect;
    dest_rect.w = m_image->width();
    dest_rect.h = m_image->height();
    dest_rect.x = static_cast<int>(round(m_position.x));
    dest_rect.y = static_cast<int>(round(m_position.y));
    
    if (m_active)
    {
        m_image->render(renderer, dest_rect, SDL_FLIP_NONE, m_degrees);
    }
}

void Player::set_angle(float angle)
{
    m_degrees = angle;
}

void Player::change_angle_to(float delta_degrees)
{
    set_angle(m_degrees + delta_degrees);
    if (m_degrees > 359.0)
    {
        set_angle(m_degrees - 360.0);
    }
    if (m_degrees < 0.0)
    {
        set_angle(360.0);
    }
}

void Player::move_forward(float delta, int window_width, int window_height, int forward )
{
    Vector2 turnvect;
    Vector2 b;
    Vector2 move_position;
    turnvect = Vector2::make_rotation(m_rad_moving);

   /* b.x = -turnvect.y * m_position.y / turnvect.x;
    b.y = m_position.y;
    b = b.normalized();*/

    switch (forward)
    {
    case 1:
        move_position = m_position + turnvect * m_speed * delta;
        break;
    case 2:
        move_position = m_position - turnvect * m_speed * delta;
        break;
    case 3:
      //  move_position = m_position - b * SPEED * delta;
        break;
    case 4:
    //    move_position = m_position + b * SPEED * delta;
        break;
    }

    move_position = is_inside_window(move_position, window_width, window_height);
    set_position(move_position);
}

void Player::speed_up(float delta, int window_width, int window_height)
{
    set_speed(m_speed + m_acceleration);
    set_forward(true);
    m_rad_moving = radians();
    move_forward(delta, window_width, window_height, 1);
}

void Player::speed_down(float delta, int window_width, int window_height)
{
    if (m_is_forward)
    {
        set_speed(m_speed - m_acceleration);
        m_rad_moving = radians();
        move_forward(delta, window_width, window_height, 1);
    }
    if (m_speed <= 100)
    {
        set_forward(false);
        m_rad_moving = radians();
        move_forward(delta, window_width, window_height, 2);
    }
}

Vector2 Player::is_inside_window(Vector2 position, int window_width, int window_height)
{
    Vector2 result;
    float max_x = window_width - m_image->width();
    if (position.x < 0)
        result.x = max_x;
    else if (position.x >= max_x)
        result.x = 0;
    else
        result.x = position.x;

    float max_y = window_height - m_image->height();

    if (position.y < 0)
        result.y = max_y;
    else if (position.y >= max_y)
        result.y = 0;
    else
        result.y = position.y;
    
    return result;
}

void Player::rotate_to_mouse(const Vector2& point)
{
    Vector2 mouse;
    mouse = point - center();
    mouse = mouse.normalized();
    Vector2 direct_pos = Vector2::make_rotation(radians());

    float ang = Vector2::angle(direct_pos, mouse);

    bool res = mouse.is_left(direct_pos);
    if (res)
    {
        change_angle_to(ang);
    }
    else
    {
        change_angle_to(-ang);
    }
}
