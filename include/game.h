#ifndef GAME_H
#define GAME_H
#include "3D_tools.h"
#include "algorithm"
#include "ball.h"
#include "math.h"
#include <GL/gl.h>
#include <GL/glu.h>

class Game {
public:
  Game(Ball b, Corridor c, Racket r);

  /* ********** F U N C T I O N S ********** */

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