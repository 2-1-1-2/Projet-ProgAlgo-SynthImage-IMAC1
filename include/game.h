#ifndef GAME_H
#define GAME_H
#include "3D_tools.h"
#include <algorithm>
#include "ball.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Game 
{
  public:
    Game(Ball b, Corridor c, Racket r);
    void isThereBonus(std::vector<Bonus>& v_bonus);
    void drawBonus(std::vector<ImgTexture>& v_texture);

    /* ********** F U N C T I O N S ********** */
    bool gameOver();
    /* ********** G E T T E R S ********** */
    Ball &getBall();
    Corridor &getCorridor();
    Racket &getRacket();
    int getLife();
    bool getGlue();
    bool getLose();

    /* ********** S E T T E R S ********** */
    void setLife(int life);
    void setGlue(bool glue);
    void setLose(bool lose);

  private:
    Ball m_ball;
    Corridor m_corridor;
    Racket m_racket;
    int m_life;
    bool m_glue;
    bool m_lose;
};
#endif