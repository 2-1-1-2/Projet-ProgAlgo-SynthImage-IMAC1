#include "racket.h"

Racket::Racket(float x, float y, float z) {
  this->m_x = x;
  this->m_y = y;
  this->m_z = z;
  this->m_length = 2.5;
  this->m_pos = 0;
  this->m_speed = 0.3;
  this->m_mode = GL_LINE_LOOP;
}

void Racket::drawRacket() {

  glColor3f(1, 0, 1);
  glLineWidth(2);
  glBegin(this->m_mode);
  glVertex3f(m_x + m_length, m_y, m_z + m_length);
  glVertex3f(m_x - m_length, m_y, m_z + m_length);
  glVertex3f(m_x - m_length, m_y, m_z - m_length);
  glVertex3f(m_x + m_length, m_y, m_z - m_length);
  glEnd();

  glBegin(GL_POINTS);
  glVertex3f(m_x, m_y, m_z);
  glEnd();
}

/* ********** G E T T E R S ********** */
int Racket::getPos() { return this->m_pos; }

/* ********** S E T T E R S ********** */
void Racket::setPos() { this->m_pos += m_speed; }

void Racket::setPos(float posX, float posY) {
  this->m_x = posX;
  this->m_z = posY;
}

void Racket::setMode() {
  this->m_mode = this->m_mode == GL_LINE_LOOP ? GL_POLYGON : GL_LINE_LOOP;
}