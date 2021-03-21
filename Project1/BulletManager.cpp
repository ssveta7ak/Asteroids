#include "BulletManager.h"

BulletManager::BulletManager()
{}

BulletManager::~BulletManager()
{}

void BulletManager::init(SDL_Renderer* renderer)
{
    for (int i = 0; i < m_bullets.size(); ++i)
    {
        m_bullet = std::make_unique<Bullet>();
        m_bullet->init(renderer);
        m_bullets.at(i) = std::move(m_bullet);
    }
}

std::unique_ptr<Bullet>& BulletManager::operator[] (const int index)
{
    return m_bullets[index];
}

void BulletManager::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < m_bullets.size(); ++i)
    {
        if (m_bullets[i]->is_active())
        {
            m_bullets[i]->render(renderer);
        }
    }
}

void BulletManager::update_fire_bullet(int window_width, int window_height, float delta)
{
    for (int i = 0; i < m_bullets.size(); ++i)
    {
        if (m_bullets[i]->is_active())
        {
            m_bullets[i]->update(delta);
             bool is_in_window = m_bullets[i]->is_inside_window(window_width, window_height);
            if (!is_in_window)
            {
                m_bullets[i]->set_active(false);
                m_bullets[i]->set_position(Vector2(0, 0));
            }
        }
    }
}
