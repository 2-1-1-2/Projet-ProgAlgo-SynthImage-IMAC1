#ifndef GAME_H
#define GAME_H
#include "3D_tools.h"
#include "ball.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <algorithm>
#include <math.h>

class Game {
public:
  Game(Ball b, Corridor c, Racket r);

  /* ********** F U N C T I O N S ********** */
  void collision(std::vector<Enemy> v_enemys, float posX, float posY,
                 int flag_walk);
  /* ********** G E T T E R S ********** */
  Ball &getBall();
  Corridor &getCorridor();
  Racket &getRacket();

  /* ********** S E T T E R S ********** */

private:
  Ball m_ball;
  Corridor m_corridor;
  Racket m_racket;
};
#endif