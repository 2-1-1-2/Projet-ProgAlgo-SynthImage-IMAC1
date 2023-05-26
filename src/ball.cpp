#include "ball.h"

Ball::Ball(float x, float y, float z) {
  m_x = x;
  m_y = y;
  m_z = z;
  m_size = 32;
  m_speedX = 0;
  m_speedY = 0.3;
  m_speedZ = 0;
  m_mode = 1; // 1 sticky, -1 rebond
}


  /* ********** F U N C T I O N S ********** */
void Ball::drawBall() {
  glColor3f(1, 1, 1);
  GLUquadricObj *quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  // gluDeleteQuadric(quadric);
  gluSphere(quadric, 1, m_size, m_size);
}


bool Ball::collisionRacket(Racket r){
  //On vérifie si c'est sur le même Y
  if((int)m_y != r.getPos('Y')) return false;
  float d_x = r.getPos('X') - m_x ;
  float d_z = r.getPos('Z') - m_z ;
  printf("dX %f, DZ %f RposX %f RposZ %f\n", abs(d_x), abs(d_z),r.getPos('X'),r.getPos('Z'));
  if(abs(d_x) > r.getLength() || abs(d_z) > r.getLength()) return false;

  m_speedX = (d_x)/2.5;
  m_speedZ = (d_z)/2.5;
  m_speedY = -m_speedY;
  printf("SPEED X : %f", m_speedX);
return true;
}
/* ********** G E T T E R S ********** */
float Ball::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}
int Ball::getMode() {
  return m_mode; 
}

/* ********** S E T T E R S ********** */

void Ball::move(float posX, float posY) {
  if (m_mode == -1){
    if(m_y > 20 || m_y< DISTANCE-10) m_speedY = -m_speedY;
    m_x += m_speedX;
    m_y += m_speedY;
    m_z += m_speedZ;
  }
  else {
    m_x = posX;
    m_z = posY;
  }
}


void Ball::setMode() {
  m_mode = -m_mode; 
}
