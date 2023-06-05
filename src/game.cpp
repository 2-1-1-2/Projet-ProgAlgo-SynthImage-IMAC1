#include "../include/game.h"
#include "../include/3D_tools.h"
#include "../include/draw_scene.h"
#include "../include/menu.h"
#include <algorithm>
#include <cstdio>

Game::Game(Ball b, Corridor c, Racket r) {
  m_ball = Ball(b.getPos('X'), b.getPos('Y'), b.getPos('Z'));
  m_corridor =
      Corridor(c.getPos('X'), c.getPos('Y'), c.getPos('Z'), c.getSpeed());
  m_racket = Racket(r.getPos('X'), r.getPos('Y'), r.getPos('Z'));
  m_life = 5;
  m_score = 0;
  m_glue = false;
  m_lose = false;
  m_collision_racket = false;
  m_texture = 1;
}

void Game::reset() {
  m_life = 5;
  m_corridor.setWalk(0);
  m_score = 0;
  m_life = 5;
  m_score = 0;
  m_glue = false;
  m_lose = false;
  m_collision_racket = false;
}

void Game::collision(std::vector<Enemy> v_enemys, float posX, float posY,
                     int flag_walk) {
  if (flag_walk) {

    // m_ball.collision(m_corridor, m_racket, v_enemys, m_glue);

    m_corridor.collision(m_racket, v_enemys);
  }
  if (m_ball.collision(m_corridor, m_racket, v_enemys, m_glue,
                       &m_collision_racket) < 0)
    m_life--;
  m_ball.move(posX, posY);
  m_racket.setPos(posX, posY);
}

// Fonction pour obtenir la valeur la plus proche d'une valeur donnée entre deux
// bornes
float clamp(float value, float min, float max) {
  if (value < min)
    return min;
  if (value > max)
    return max;
  return value;
}

void Game::isThereBonus(std::vector<Bonus> &v_bonus) 
{
  for (auto it = v_bonus.begin(); it != v_bonus.begin()+1; ++it) 
  {
    Bonus &bonus = *it;

    //printf("ON EST SUR LE MEME KILOMETRE %f %f\n", m_racket.getPos('Y'), bonus.getD());
    if(m_racket.getPos('Y') + 1 >= bonus.getD() && m_racket.getPos('Y') <= bonus.getD())
    {
      float r_x = m_racket.getPos('X');
      float r_z = m_racket.getPos('Z');
      float r_h = m_racket.getLength();

      float b_x = bonus.getX();
      float b_z = bonus.getZ();
      float b_r = bonus.getH();

      float racketLeft = r_x - r_h;
      float racketRight = r_x + r_h;
      float racketTop = r_z + r_h;
      float racketBottom = r_z - r_h;

      // Calcul des coordonnées du cercle pour la collision
      float circleX = b_x;
      float circleZ = b_z;

      // Vérifier la collision entre le carré et le cercle
      float closestX = clamp(circleX, racketLeft, racketRight);
      float closestZ = clamp(circleZ, racketBottom, racketTop);
      float distanceX = circleX - closestX;
      float distanceZ = circleZ - closestZ;
      float distanceSquared = distanceX * distanceX + distanceZ * distanceZ;

      if (distanceSquared <= b_r * b_r) {
        printf("JE TE RAMASSE\n");
        // La vie
        if (bonus.getType() == 0 && m_life != 5)
          m_life += 1;
        // La colle
        else if (bonus.getType() == 1)
          m_glue = true;

        m_score += 100;
        // Enlever l'objet du vecteur v_bonus
        v_bonus.erase(it);
        break;
      }
    }
    else if(m_racket.getPos('Y') >= bonus.getD() + 5)
    {
      v_bonus.erase(it);
      break;
    }
  }
}

void Game::drawBonus(std::vector<ImgTexture> &v_texture) {
  float x = -22.5;
  float y = -14;
  float z = -16;
  float h = 3;

  drawTexture(v_texture[5].img);

  for (int i = 0; i < m_life; i++) {
    drawCircle(x, y, z, h);
    x += 2.5;
    y -= 0.1;
  }
  finTexture();

  if (m_glue) {
    x = 0;
    z = -16;
    drawTexture(v_texture[6].img);
    drawCircle(x, y, z, h);
    finTexture();
  }
}

bool Game::gameOver() {
  m_lose = true;
  return m_life <= 0;
}

/* ********** G E T T E R S ********** */
Ball &Game::getBall() { return m_ball; }
Corridor &Game::getCorridor() { return m_corridor; }
Racket &Game::getRacket() { return m_racket; }
Menu &Game::getMenu() { return m_menu; }
int Game::getLife() { return m_life; }
bool Game::getGlue() { return m_glue; }
bool Game::getLose() { return m_lose; }
float Game::getScore() { return m_score; }
bool Game::getCollisionRacket() { return m_collision_racket; }
int Game::getTexture() { return m_texture; }

/* ********** S E T T E R S ********** */
void Game::setLife(int life) { m_life = life; }

void Game::setGlue(bool glue) { m_glue = glue; }

void Game::setLose(bool lose) { m_lose = lose; }

void Game::setScore() { m_score += 0.3f; }
void Game::setTexture(int texture) { m_texture = texture; }