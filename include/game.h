#ifndef GAME_H
#define GAME_H
#include "3D_tools.h"
#include "ball.h"
#include "menu.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <algorithm>

class Game 
{
  public:
    Game(Ball b, Corridor c, Racket r);

    /* ********** F U N C T I O N S ********** */
    void collision(std::vector<Enemy> v_enemys, float posX, float posY,
                 int flag_walk);
    void isThereBonus(std::vector<Bonus>& v_bonus);
    void drawBonus(std::vector<ImgTexture>& v_texture);
    bool gameOver();

    /* ********** G E T T E R S ********** */
    Ball &getBall();
    Corridor &getCorridor();
    Racket &getRacket();
    Menu &getMenu();
    int getLife();
    bool getGlue();
    bool getLose();
    float getScore();

    /* ********** S E T T E R S ********** */
    void setLife(int life);
    void setGlue(bool glue);
    void setLose(bool lose);
    void setScore();
    bool getCollisionRacket();

  private:
    Ball m_ball;
    Corridor m_corridor;
    Racket m_racket;
    Menu m_menu;
    int m_life;
    float m_score;
    bool m_glue;
    bool m_lose;
    bool m_collision_racket;
};
#endif