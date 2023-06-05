#include "../include/ball.h"

Ball::Ball(float x, float y, float z) {
  m_x = x;
  m_y = y;
  m_z = z;
  m_size = 32;
  m_speedX = 0;
  m_speedY = 0.5;
  m_speedZ = 0;
  m_mode = 1; // 1 sticky, -1 rebond
}

/* ********** F U N C T I O N S ********** */
void Ball::drawBall() 
{
  glColor3f(1, 1, 1);
  GLUquadricObj *quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  // gluDeleteQuadric(quadric);
  gluSphere(quadric, 2, m_size, m_size);
}

bool Ball::collisionRacket(Racket r, bool glue) {
  // On vérifie si c'est sur le même Y
  if ((int)m_y != r.getPos('Y')-1)
    return false;
  float d_x = r.getPos('X') - m_x;
  float d_z = r.getPos('Z') - m_z;
  if (abs(d_x) - (m_size / (6. * M_PI)) > r.getLength() || abs(d_z)- (m_size / (6. * M_PI)) > r.getLength())
    return false;
  // Bonus de colle
  if(glue && m_mode != 1)
    m_mode = -m_mode;
  else
  {
    m_speedX = (d_x) / (r.getLength() * 2);
    m_speedZ = (d_z) / (r.getLength() * 2);
    m_y += r.getLength();
    m_speedY *= -1;
  }

  //TODO gérer écart sur les coins => game over automatique sinon
  return true;
}

/*
bool Ball::collisionRacket(Mur m) { //Liste de mur
  // On vérifie si c'est sur le même Y
  if ((int)m_y != m.getPos('Y'))
    return false;
  float d_x = m.getPos('X') - m_x;
  float d_z = m.getPos('Z') - m_z;
  printf("dX %f, DZ %f RposX %f RposZ %f\n", abs(d_x), abs(d_z), m.getPos('X'),
         m.getPos('Z'));
  if (abs(d_x) > m.getLength() || abs(d_z) > m.getLength())
    return false;

  m_speedX = (d_x) / 2.5;
  m_speedZ = (d_z) / 2.5;
  m_y += 0.3;
  m_speedY *= -1;
  printf("SPEED X : %f", m_speedX);
  return true;
}
*/

int Ball::collisionCorridor(Corridor c) {
  // On vérifie si c'est sur le même Y
  int res = 0; // 0 rien, 1 GD, 2 HB, 3 GBHB

  if (abs(m_x) + (m_size / (6. * M_PI)) > abs(c.getPos('X'))) {
    m_speedX *= -1;
    res += 1;
  }
  if (abs(m_z) + (m_size / (6. * M_PI)) > abs(c.getPos('Z'))) {
    m_speedZ *= -1;
    res += 2;
  }

  return res;
}

bool Ball::collision(Corridor c, Racket r, bool glue) {
  collisionCorridor(c);
  if(collisionRacket(r, glue))
    return true;
  return false;
}

/* ********** G E T T E R S ********** */
float Ball::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}

int Ball::getMode() { return m_mode; }

/* ********** S E T T E R S ********** */
void Ball::move(float posX, float posY) {
  if (m_mode == -1) {
    if (m_y > 50 || m_y < DISTANCE - 10)
      m_speedY *= -1;
    m_x += m_speedX;
    m_y += m_speedY;
    m_z += m_speedZ;
  } else {
    m_x = posX;
    m_z = posY;
  }
}

void Ball::setMode() { m_mode = -m_mode; }

void Ball::setPos(char pos, float p) {
  switch (pos)
  {
    case 'X': m_x = p; break;
    case 'Y': m_y = p; break;
    case 'Z': m_z = p; break;
  default:
    break;
  }
}