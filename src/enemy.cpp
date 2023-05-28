#include "enemy.h"

Enemy::Enemy()
{
    this->m_w = 0;
    this->m_h = 0;
    this->m_d = 0;
    this->m_points = 0;
    this->m_left = -1;
    this->m_up = -1;
    this->m_rot = -1;
}

Enemy::Enemy(int w, int h, int d, int points, int left, int up)
{
    this->m_w = w;
    this->m_h = h;
    this->m_d = d;
    this->m_points = points;
    this->m_left = left;
    this->m_up = up;
    this->m_rot = -1;
}

    /* Constructeur de copie */
Enemy::Enemy (const Enemy &e)
{
    m_w = e.m_w;
    m_h = e.m_h;
    m_d = e.m_d;
    m_points = e.m_points;
    m_left = e.m_left;
    m_up = e.m_up;
    m_rot = e.m_rot;
}

/* ********** G E T T E R S ********** */
int Enemy::getW() {
    return m_w;
}

int Enemy::getH() {
    return m_h;
}

float Enemy::getD() {
    return m_d;
}

int Enemy::getLeft() {
    return m_left;
}

int Enemy::getUp() {
    return m_up;
}

int Enemy::getRot() {
    return m_rot;
}

/* ********** G E T T E R S ********** */
void Enemy::setD(float d) {
    m_d = d;
}

void Enemy::setDWithWalk(float walk) {
    m_d -= walk;
}

void Enemy::setRot(int rot) {
    m_rot = rot;
}