#ifndef BALL_H
#define BALL_H
#include "3D_tools.h"
#include <algorithm>
#include "corridor.h"
#include <math.h>
#include "racket.h"
#include <GL/gl.h>
#include <GL/glu.h>

class Ball {
public:
  Ball(float x, float y, float z);
  Ball(){};

  /* ********** F U N C T I O N S ********** */
  void drawBall();
  bool collisionRacket(Racket r, bool glue);
  int collisionCorridor(Corridor c);
  bool collision(Corridor c, Racket r, bool glue);
  /* ********** G E T T E R S ********** */
  float getPos(char pos);
  int getMode();
  /* ********** S E T T E R S ********** */
  void move(float posX, float posY);
  void setMode();
  void setPos(char pos, float p);

private:
  float m_x;
  float m_y;
  float m_z;
  int m_size;
  float m_speedX;
  float m_speedY;
  float m_speedZ;
  int m_mode;
};
#endif