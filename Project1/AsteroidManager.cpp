#include "AsteroidManager.h"

Asteroidmanager::Asteroidmanager()
{}

Asteroidmanager::~Asteroidmanager()
{}

void Asteroidmanager::init(SDL_Renderer* renderer)
{
    for (int i = 0; i < m_asteroids.size(); ++i)
    {
        m_asteroid = std::make_unique<Asteroid>();
        m_asteroid->init(renderer);
        m_asteroids.at(i) = std::move(m_asteroid);
    }
}

std::unique_ptr<Asteroid>& Asteroidmanager::operator[] (const int index)
{
    return m_asteroids[index];
}

void Asteroidmanager::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < m_asteroids.size(); ++i)
    {
        if (m_asteroids[i]->is_active())
        {
            m_asteroids[i]->render(renderer);
        }
    }
}

void Asteroidmanager::update(int window_width, int window_height, float delta)
{
    for (int i = 0; i < m_asteroids.size(); ++i)
    {
        if (m_asteroids[i]->is_active())
        {
            m_asteroids[i]->update(delta, window_width, window_height);
        }
       // bool is_in_window = m_asteroids[i]->is_inside_window(window_width, window_height);
       
    }

}

