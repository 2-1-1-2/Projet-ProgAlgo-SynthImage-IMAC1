#include "../include/enemy.h"

Enemy::Enemy() {
  this->m_w = 0;
  this->m_h = 0;
  this->m_d = 0;
  this->m_points = 0;
  this->m_left = -1;
  this->m_up = -1;
  this->m_rot = -1;
}

Enemy::Enemy(int m_w, int m_h, int d, int points, int left, int up) {
  this->m_w = m_w;
  this->m_h = m_h;
  this->m_d = d;
  this->m_points = points;
  this->m_left = left;
  this->m_up = up;
  this->m_rot = -1;
}

/* Constructeur de copie */
Enemy::Enemy(const Enemy &e) {
  m_w = e.m_w;
  m_h = e.m_h;
  m_d = e.m_d;
  m_points = e.m_points;
  m_left = e.m_left;
  m_up = e.m_up;
  m_rot = e.m_rot;
}
/* ********** F U N C T I O N S ********** */
bool Enemy::contains(float posX, float posZ, float cx, float cz) {

  /* *** Enemy is completely horizontal *** */
  if (getLeft() == -1 && getUp() != -1) {
    if ((!getUp() && posZ < -cz + m_h) || (getUp() && posZ > cz - m_h)) {
      return true;
    }
  }
  /* *** Enemy is completely vertical *** */
  if (getUp() == -1 && getLeft() != -1) {
    if ((getLeft() == 1 && posX <= -cx + m_w) ||
        (!getLeft() && posX >= cx - m_w)) {
      return true;
    }
  }

  // cas carré
  if (getLeft() != -1 && getUp() != -1) {
    if ((getLeft() == 1 && posX <= -cx + m_w) ||
        (!getLeft() && posX >= cx - m_w) && (!getUp() && posZ < -cz + m_h) ||
        (getUp() && posZ > cz - m_h)) {
      printf("c'est carré !!\n");
      return true;
    }
  }
  return false;
}

/* ********** G E T T E R S ********** */
int Enemy::getW() { return m_w; }

int Enemy::getH() { return m_h; }

float Enemy::getD() { return m_d; }

int Enemy::getLeft() { return m_left; }

int Enemy::getUp() { return m_up; }

int Enemy::getRot() { return m_rot; }

/* ********** G E T T E R S ********** */
void Enemy::setD(float d) { m_d = d; }

void Enemy::setDWithWalk(float walk) { m_d -= walk; }

void Enemy::setRot(int rot) { m_rot = rot; }