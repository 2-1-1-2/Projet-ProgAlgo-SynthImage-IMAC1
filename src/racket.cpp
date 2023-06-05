#include "../include/racket.h"

Racket::Racket(float x, float y, float z) {
  m_x = x;
  m_y = y;
  m_z = z;
  m_length = 2.5;
  m_pos = 0;
  m_speed = 0.3;
  m_mode = GL_POLYGON;
}

void Racket::drawRacket() {

  glColor3f(1, 0, 1);
  glLineWidth(2);
  glBegin(GL_LINE_LOOP);
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
float Racket::getPos(char pos) { return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z; }

float Racket::getLength() {return m_length;}

/* ********** S E T T E R S ********** */
void Racket::setPos() { m_pos += m_speed; }

void Racket::setPos(float posX, float posY) {
  m_x = posX;
  m_z = posY;
}

void Racket::setMode() {
  m_mode = m_mode == GL_LINE_LOOP ? GL_POLYGON : GL_LINE_LOOP;
}