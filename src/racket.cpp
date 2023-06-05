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

  static GLfloat vCompColor[4];
  vCompColor[0] = 104. / 255.;
  vCompColor[1] = 42. / 255.;
  vCompColor[2] = 115. / 255.;
  vCompColor[3] = .5f;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, vCompColor);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vCompColor);

  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
  glColor4f(104., 42., 115., 0.5);
  glLineWidth(2);

  glBegin(m_mode);
    glVertex3f(m_x + m_length, m_y - 4, m_z + m_length);
    glVertex3f(m_x - m_length, m_y - 4, m_z + m_length);
    glVertex3f(m_x - m_length, m_y - 4, m_z - m_length);
    glVertex3f(m_x + m_length, m_y - 4, m_z - m_length);
  glEnd();

  glBegin(GL_POINTS);
    glVertex3f(m_x, m_y, m_z);
  glEnd();
}

/* ********** G E T T E R S ********** */
float Racket::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}

float Racket::getLength() {return m_length; }

/* ********** S E T T E R S ********** */
void Racket::setPos() { m_pos += m_speed; }

void Racket::setPos(float posX, float posY) {

  float RIGHT = CORRIDOR_WIDTH - m_length;
  float TOP = CORRIDOR_HEIGHT - m_length;
  m_x = posX > RIGHT ? RIGHT : posX < -RIGHT ? -RIGHT : posX;
  m_z = posY > TOP ? TOP : posY < -TOP ? -TOP : posY;
}

void Racket::setMode() {
  m_mode = m_mode == GL_LINE_LOOP ? GL_POLYGON : GL_LINE_LOOP;
}