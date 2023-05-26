#ifndef RACKET_H
#define RACKET_H
#include "3D_tools.h"
#include <algorithm>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Racket {
public:
  Racket(float x, float y, float z);
  Racket(){};

  /* ********** F U N C T I O N S ********** */
  void drawRacket();

  /* ********** G E T T E R S ********** */
  float getPos(char pos);
  float getLength();

  /* ********** S E T T E R S ********** */
  void setPos();
  void setPos(float posX, float posY);
  void setMode();

private:
  float m_x;
  float m_y;
  float m_z;
  float m_length;
  float m_pos;
  float m_speed;
  GLenum m_mode;
};
#endif