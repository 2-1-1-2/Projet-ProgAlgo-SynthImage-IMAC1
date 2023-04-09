#include "ennemy.h"

Enemy::Enemy(int w, int h, int points, bool left)
{
    this->m_w = w;
    this->m_h = h;
    this->m_points = points;
    this->m_left = left;
}