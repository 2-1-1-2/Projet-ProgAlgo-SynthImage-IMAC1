#include "enemy.h"

Enemy::Enemy(int w, int h, int km, int points, bool left)
{
    this->m_w = w;
    this->m_h = h;
    this->m_d = 40;
    this->m_km = km;
    this->m_points = points;
    this->m_left = left;
}

/* ********** G E T T E R S ********** */
int Enemy::getW()
{
    return m_w;
}

int Enemy::getH()
{
    return m_h;
}

float Enemy::getD()
{
    return m_d;
}

bool Enemy::getLeft()
{
    return m_left;
}

/* ********** G E T T E R S ********** */
void Enemy::setD(float d)
{
    m_d = d;
}

void Enemy::setDWithWalk(float walk)
{
    m_d -= walk;
}