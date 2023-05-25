#include "ball.h"

Ball::Ball(float x, float y, float z) {
  m_x = x;
  m_y = y;
  m_z = z;
  m_size = 32;
  m_speed = 0.3;
  m_mode = 0; // 0 sticky, 1 rebond
}

void Ball::drawBall() {

  glColor3f(1, 1, 1);
  GLUquadricObj *quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  // gluDeleteQuadric(quadric);
  gluSphere(quadric, 1, m_size, m_size);
}

/* ********** G E T T E R S ********** */
float Ball::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}
/* ********** S E T T E R S ********** */

void Ball::setPos(float posX, float posY) {
  m_x = posX;
  m_z = posY;
  if (m_mode == 1)
    m_y += m_speed;
}
