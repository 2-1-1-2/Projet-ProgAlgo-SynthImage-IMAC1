#ifndef BALL_H
#define BALL_H
#include "3D_tools.h"
#include "corridor.h"
#include "enemy.h"
#include "racket.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <algorithm>
#include <math.h>
#include <vector>

class Ball {
public:
  Ball(float x, float y, float z);
  Ball(){};

  /* ********** F U N C T I O N S ********** */
  void drawBall();
  int collisionRacket(Racket r, bool glue, bool *collision_racket);
  bool collisionEnemy(std::vector<Enemy> v_enemys, float cx, float cz);
  int collisionCorridor(Corridor c);
  int collision(Corridor c, Racket r, std::vector<Enemy> v_enemys, bool glue,
                bool *collision_racket);
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
  float m_radius;
  int m_size;
  float m_speedX;
  float m_speedY;
  float m_speedZ;
  int m_mode;
};
#endif