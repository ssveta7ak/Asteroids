#pragma once

#include "SDL.h"
#include <iostream>
#include "Image.h"
#include "Vector2.h"
#include "Object.h"


class Player: public Object
{
public:
    Player();
    ~Player();

    
    virtual void init(SDL_Renderer* renderer) override;
    virtual void render(SDL_Renderer* renderer) override;
    Vector2 is_inside_window( Vector2 position, int window_width, int window_height);
    void set_angle(float angle);
    void change_angle_to(float delta_degrees);
    float degrees() const { return m_degrees; }
    float radians() { return m_degrees * M_PI / 180.0; }
    void move_forward(float delta, int window_width, int window_height, int forward);
    void speed_up(float delta, int window_width, int window_height);
    void speed_down(float delta, int window_width, int window_height);
    bool is_forward() const { return m_is_forward; }
    void set_forward(bool value) { m_is_forward = value;}
    float get_acceleration() { return m_acceleration; }
    void rotate_to_mouse(const Vector2& vec);
    void set_rad_moving(float rad_moving) { m_rad_moving = rad_moving; }
   
private:
    bool m_is_forward = true;
    float m_degrees = 0; //Angle of rotation
    float m_rad_moving = 0;
    float m_acceleration = 3;
};
