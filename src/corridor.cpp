#include "../include/corridor.h"
#include "../include/3D_tools.h"
#include "../include/bonus.h"
#include "algorithm"
#include <GL/gl.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

Corridor::Corridor(int x, int y, int z, float speed) {
  this->m_x = x;
  this->m_y = y;
  this->m_z = z;
  this->m_start = -14;
  this->m_walk = 0;
  this->m_speed = 0.3f;

  /*float colors[6] = {0.5, 0.5, 1, 0.5, 0.8, 1};
  std::copy(colors, colors + 6, m_colors);*/

  int temp = y;
  for (size_t i = 0; i < 7; i++) {
    m_lines[i] = temp;
    temp -= 10;
  }
}

/* ********** F U N C T I O N ********** */
int randomInt(int min, int max) {
  // Vérification des limites
  if (min > max) {
    std::swap(min, max);
  }

  // Calcul de l'intervalle
  int range = max - min + 1;

  // Génération de l'entier aléatoire dans l'intervalle spécifié
  int randomValue = std::rand() % range + min;

  return randomValue;
}

bool Corridor::collisionRacket(Racket r, std::vector<Enemy> v_enemys, float cx,
                               float cz) { // Liste de mur
  // On vérifie si c'est sur le même Y
  for (Enemy element : v_enemys) {
    if (element.getD() > r.getPos('Y') + RADIUS_CIRCLE * 2 ||
        element.getD() < DISTANCE / 5 - 1)
      continue;
    //(int)(m_km + r.getPos('Y') - 0.5)
    // printf("RAACKET pos %f\n", r.getPos('X'));
    if (element.contains(r.getPos('X'), r.getPos('Z'), cx, cz)) {
      /*printf("RACKET MUR DEPTH %f (m_km + r.getPos('Y')) %f m_km %f cc %d pos
         " "X_rack %f\n", element.getD(), (m_km + r.getPos('Y')), m_km, (m_km >
         element.getD()), r.getPos('X'));*/
      return true;
    }
  }
  return false;
}

void Corridor::collision(Racket r, std::vector<Enemy> v_enemys) {
  if (!collisionRacket(r, v_enemys, getPos('X'), getPos('Z')))
    setWalk();
}

void Corridor::drawCorridor(std::vector<ImgTexture> &v_texture) {
  static GLfloat vCompColor[4];
  vCompColor[0] = 1.0f;
  vCompColor[1] = 1.0f;
  vCompColor[2] = 1.0f;
  vCompColor[3] = 1.0f;
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, vCompColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, vCompColor);

  glColor3f(145 / 255., 82 / 255., 157 / 255.);

  // drawTexture(v_texture[3].img);
  drawA(m_x, m_y, -m_z, m_start, true);
  // finTexture();
  //   top square
  // drawTexture(v_texture[2].img);
  drawA(m_x, m_y, m_z, m_start, true);
  // finTexture();

  // drawTexture(v_texture[1].img);
  //   left square
  drawA(-m_x, m_y, m_z, m_start, false);
  // right square
  drawA(m_x, m_y, m_z, m_start, false);
  // finTexture();
}

void Corridor::drawBonus(std::vector<Bonus> &v_bonus,
                         std::vector<ImgTexture> &v_texture) {
  for (Bonus &bonus : v_bonus) {
    // to make walk the bonus
    bonus.setDWithWalk(m_walk);

    int x = bonus.getX();
    int z = bonus.getZ();
    int h = bonus.getH();

    // La vie
    if (bonus.getType() == 0)
      drawTexture(v_texture[8].img);
    // La colle
    else
      drawTexture(v_texture[9].img);

    drawCircle(x, bonus.getD(), z, h);
    finTexture();
  }
}

void Corridor::drawEnemys(std::vector<Enemy> &v_enemys,
                          std::vector<ImgTexture> &v_texture) {
  for (Enemy &element : v_enemys) {
    // to make walk the enemys
    element.setDWithWalk(m_walk);

    if (element.getLeft() != -1 && element.getUp() != -1) {
      drawTexture(v_texture[7].img);
      // Gauche
      if (element.getLeft()) {
        // Haut
        if (element.getUp())
          drawEnemy(-m_x, -m_x + element.getW(), element.getD(),
                    m_z - element.getH(), m_z);
        // Bas
        else
          drawEnemy(-m_x, -m_x + element.getW(), element.getD(), -m_z,
                    -m_z + element.getH());
      }
      // Droite
      else {
        // Haut
        if (element.getUp())
          drawEnemy(m_x - element.getW(), m_x, element.getD(),
                    m_z - element.getH(), m_z);
        // Bas
        else
          drawEnemy(m_x - element.getW(), m_x, element.getD(), -m_z,
                    -m_z + element.getH());
      }
      finTexture();
    }
    /* *** Enemy is completely horizontal *** */
    else if (element.getLeft() == -1) {
      if (element.getUp()) {
        drawTexture(v_texture[6].img);
        drawHorizontalEnemy(m_x, element.getD(), m_z - element.getH(), m_z);
      } else {
        drawTexture(v_texture[5].img);
        drawHorizontalEnemy(m_x, element.getD(), -m_z, -m_z + element.getH());
      }
      finTexture();
    }
    /* *** Enemy is completely vertical *** */
    else {
      drawTexture(v_texture[4].img);
      // Picture can be upside down
      if (v_texture[4].rot && element.getRot() == -1)
        element.setRot(rand() % 2);

      if (element.getLeft())
        drawVerticalEnemy(-m_x, -m_x + element.getW(), element.getD(), m_z,
                          element.getRot());
      else
        drawVerticalEnemy(m_x, m_x - element.getW(), element.getD(), m_z,
                          element.getRot());

      finTexture();
    }
  }
}

// to make go backward the inside of the corridor
void Corridor::drawLines(std::vector<Enemy> &v_enemys,
                         std::vector<Bonus> &v_bonus,
                         std::vector<ImgTexture> &v_texture) {
  // color white

  static GLfloat vCompColor[4];
  vCompColor[0] = 0.9f;
  vCompColor[1] = 0.9f;
  vCompColor[2] = 0.9f;
  vCompColor[3] = 1.0f;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, vCompColor);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vCompColor);
  glColor3f(1, 1, 1);
  // size of the line
  glLineWidth(2);
  // To create the 7 lines
  for (size_t i = 0; i < 7; i++) {
    m_lines[i] -= m_walk;

    if (m_lines[i] <= -10)
      m_lines[i] = m_y - 1;

    drawLineLoop(m_x, m_lines[i], m_z);
  }

  // To create the enemys
  drawEnemys(v_enemys, v_texture);

  // To create the bonus
  drawBonus(v_bonus, v_texture);

  m_walk = 0;
}

// to initialize the enemys
void Corridor::loadEnemys(std::vector<Enemy> &v_enemys) {
  std::map<std::string, std::tuple<int, int, int, int, int, int>> enemyMap;
  std::string line;
  std::ifstream file("src/enemys.txt");
  std::string e;
  int d;

  if (!file.is_open())
    perror("error while opening file\n");

  initializeEnemyMap(enemyMap);
  while (std::getline(file, line)) {
    std::istringstream iss(line);

    if (!(iss >> e >> d))
      perror("not the good number of elements");

    Enemy enemy = createEnemy(enemyMap, e, d);
    v_enemys.push_back(enemy);
  }

  if (file.bad())
    perror("error while reading file");

  file.close();
}

void Corridor::loadBonus(std::vector<Bonus> &v_bonus) {
  int km = 200;
  int h = 4;

  for (size_t i = 0; i < 5; i++) {
    int x = randomInt(-m_x, m_x);
    while (((x + h) >= m_x) || ((x - h) <= -m_x)) {
      x = randomInt(-m_x, m_x);
    }

    int z = randomInt(-m_z, m_z);
    while (((z + h) >= m_z) || ((z - h) <= -m_z)) {
      z = randomInt(-m_z, m_z);
    }

    int type = std::rand() % 2;
    Bonus bonus = Bonus(type, x, z, h, km);
    v_bonus.push_back(bonus);

    km += 300;
  }
}

/* ********** G E T T E R S ********** */
int Corridor::getZ() { return this->m_z; }

/*int Corridor::getKm() {
    return m_km;
}*/

int Corridor::getWalk() { return m_walk; }

int Corridor::getSpeed() { return m_speed; }

float Corridor::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}

/* ********** S E T T E R S ********** */
void Corridor::setWalk() { this->m_walk += m_speed; }

void Corridor::setWalk(int walk) { m_walk = walk; }