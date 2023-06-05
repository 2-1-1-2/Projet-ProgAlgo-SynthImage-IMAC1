#include "../include/corridor.h"
#include "algorithm"
#include <GL/gl.h>
#include <cstdio>

Corridor::Corridor(int x, int y, int z, float speed) {
  this->m_x = x;
  this->m_y = y;
  this->m_z = z;
  this->m_start = -14;
  this->m_walk = 0;
  this->m_km = -14;
  this->m_speed = 0.2;

  float colors[6] = {0.5, 0.5, 1, 0.5, 0.8, 1};
  std::copy(colors, colors + 6, m_colors);

  int temp = y;
  for (size_t i = 0; i < 7; i++) {
    m_lines[i] = temp;
    temp -= 10;
  }
}

/* ********** F U N C T I O N ********** */
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
      printf("RACKET MUR DEPTH %f (m_km + r.getPos('Y')) %f m_km %f cc %d pos "
             "X_rack %f\n",
             element.getD(), (m_km + r.getPos('Y')), m_km,
             (m_km > element.getD()), r.getPos('X'));
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
  // bottom square
  // drawTexture(v_texture[3].img);

  glColor3f(145 / 255., 82 / 255., 157 / 255.);
  drawSquare(m_x, m_y, -m_z, m_start, true);
  // finTexture();
  //  top square
  // drawTexture(v_texture[2].img);
  drawSquare(m_x, m_y, m_z, m_start, true);
  // finTexture();

  // drawTexture(v_texture[1].img);
  //  left square
  drawSquare(-m_x, m_y, m_z, m_start, false);
  // right square
  drawSquare(m_x, m_y, m_z, m_start, false);
  // finTexture();
}

// to make go backward the inside of the corridor
void Corridor::drawLines(std::vector<Enemy> &v_enemys,
                         std::vector<ImgTexture> &v_texture) {
  // color white
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
  for (Enemy &element : v_enemys) {
    // to make walk the enemys
    if (element.getD() < DISTANCE / 5 - 1)
      continue; // disparait quand derrière la raquette
    element.setDWithWalk(m_walk);

    if (element.getLeft() != -1 && element.getUp() != -1) {
      // drawTexture(v_texture[7].img);
      //  Gauche
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
      // finTexture();
    }
    /* *** Enemy is completely horizontal *** */
    else if (element.getLeft() == -1) {
      if (element.getUp()) {
        // drawTexture(v_texture[6].img);
        drawHorizontalEnemy(m_x, element.getD(), m_z - element.getH(), m_z);
      } else {
        // drawTexture(v_texture[5].img);
        drawHorizontalEnemy(m_x, element.getD(), -m_z, -m_z + element.getH());
      }
      // finTexture();
    }
    /* *** Enemy is completely vertical *** */
    else {
      // TODO remettre draw texture
      //  drawTexture(v_texture[4].img);
      //   Picture can be upside down
      if (v_texture[4].rot && element.getRot() == -1)
        element.setRot(rand() % 2);

      if (element.getLeft())
        drawVerticalEnemy(-m_x, -m_x + element.getW(), element.getD(), m_z,
                          element.getRot());
      else
        drawVerticalEnemy(m_x, m_x - element.getW(), element.getD(), m_z,
                          element.getRot());

      // finTexture();
    }
  }
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

/* ********** G E T T E R S ********** */
int Corridor::getZ() { return this->m_z; }

int Corridor::getWalk() { return m_walk; }

int Corridor::getSpeed() { return m_speed; }

float Corridor::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}

/* ********** S E T T E R S ********** */
void Corridor::setWalk() {
  this->m_walk += m_speed;
  this->m_km += m_speed;
  printf("Km: %f\n", m_speed);
}

void Corridor::setWalk(int walk) { m_walk = walk; }