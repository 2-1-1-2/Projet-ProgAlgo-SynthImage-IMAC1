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
  bool collisionRacket(Racket r);
  bool collisionEnemy(std::vector<Enemy> v_enemys, float cx, float cz);
  int collisionCorridor(Corridor c);
  void collision(Corridor c, Racket r, std::vector<Enemy> v_enemys);
  bool gameOver(Racket r);
  /* ********** G E T T E R S ********** */
  float getPos(char pos);
  int getMode();
  int getLife();
  /* ********** S E T T E R S ********** */
  void move(float posX, float posY);
  void setMode();
  void setPos(char pos, float p);
  void setLife(int life);
  void setKm();

private:
  float m_x;
  float m_y;
  float m_z;
  int m_life;
  int m_radius;
  int m_size;
  float m_km;
  float m_speedX;
  float m_speedY;
  float m_speedZ;
  int m_mode;
};
#endif