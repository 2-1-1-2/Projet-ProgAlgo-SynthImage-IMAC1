#ifndef BALL_H
#define BALL_H
#include "3D_tools.h"
#include "algorithm"
#include "math.h"
#include <GL/gl.h>
#include <GL/glu.h>

class Ball {
public:
  Ball(float x, float y, float z);

  /* ********** F U N C T I O N S ********** */
  void drawBall();

  /* ********** G E T T E R S ********** */
  float getPos(char pos);
  /* ********** S E T T E R S ********** */
  void setPos(float posX, float posY);

private:
  float m_x;
  float m_y;
  float m_z;
  int m_size;
  float m_speed;
  int m_mode;
};
#endif