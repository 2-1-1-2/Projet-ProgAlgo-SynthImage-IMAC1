#include "../include/ball.h"

Ball::Ball(float x, float y, float z) {
  m_x = x;
  m_y = y;
  m_z = z;
  m_life = 5;
  m_size = 32;
  m_speedX = 0;
  m_speedY = 0.2;
  m_radius = RADIUS_CIRCLE;
  m_speedZ = 0;
  m_mode = 1; // 1 sticky, -1 rebond
  m_km = 0;
}

/* ********** F U N C T I O N S ********** */
void Ball::drawBall() {
  glColor3f(1, 1, 1);
  GLUquadricObj *quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  // gluDeleteQuadric(quadric);
  gluSphere(quadric, m_radius, m_size, m_size);
}

bool Ball::gameOver(Racket r) {
  if (m_y >= r.getPos('Y') - 1)
    return false;
  setPos('X', r.getPos('X'));
  setPos('Z', r.getPos('Z'));
  setMode();
  setLife(m_life - 1);
  return m_life < 0;
}

bool Ball::collisionRacket(Racket r) {
  // On vérifie si c'est sur le même Y
  if (m_y > r.getPos('Y') - m_radius)
    return false;
  float d_x = r.getPos('X') - m_x;
  float d_z = r.getPos('Z') - m_z;
  if (abs(d_x) - m_radius * 2 > r.getLength() ||
      abs(d_z) - m_radius * 2 > r.getLength()) {
    gameOver(r);
    return false;
  }
  printf("collision raquette\n");
  m_speedX = (d_x) / (r.getLength() * 4.);
  m_speedZ = (d_z) / (r.getLength() * 4.);
  // m_y += r.getLength();

  m_speedY *= -1;

  m_y += m_speedY;
  return true;
}

int Ball::collisionCorridor(Corridor c) {
  // On vérifie si c'est sur le même Y
  int res = 0; // 0 rien, 1 GD, 2 HB, 3 GBHB

  if (abs(m_x) + m_radius > abs(c.getPos('X'))) {
    m_speedX *= -1;
    m_x += m_speedX;
    res += 1;
  }
  if (abs(m_z) + m_radius > abs(c.getPos('Z'))) {
    m_speedZ *= -1;
    m_z += m_speedZ;
    res += 2;
  }
  if (res > 0)
    printf("collision murs couloir\n");
  return res;
}
bool Ball::collisionEnemy(std::vector<Enemy> v_enemys, float cx,
                          float cz) { // Liste de mur
  // On vérifie si c'est sur le même Y
  float min = 6000;
  for (Enemy element : v_enemys) {
    min = element.getD() < min ? element.getD() : min;
    // printf("MIN %f m_y%f \n", min, m_y);

    if (((int)(m_y) == (int)(element.getD() - m_radius / 1.5) && m_speedY > 0 ||
         (int)(m_y) == (int)(element.getD() + m_radius / 1.5) &&
             m_speedY < 0) &&
        element.contains(m_x, m_z, cx, cz)) {

      printf("DEPTH %f m_km %f cc %d\n", element.getD(), m_km,
             (m_km > element.getD()));
      m_speedY *= -1;

      printf("collision mur ennemie\n");
      return true;
    }
  }
  return false;
}
int Ball::collision(Corridor c, Racket r, std::vector<Enemy> v_enemys) {
  return (collisionCorridor(c) || collisionRacket(r) ||
          collisionEnemy(v_enemys, c.getPos('X') - m_radius * 2,
                         c.getPos('Z') - m_radius * 2));
}

/* ********** G E T T E R S ********** */
float Ball::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}
int Ball::getMode() { return m_mode; }
int Ball::getLife() { return m_life; }

/* ********** S E T T E R S ********** */

void Ball::setLife(int life) { m_life = life; };

void Ball::move(float posX, float posY) {
  if (m_mode == -1) {
    m_x += m_speedX;
    m_y += m_speedY;
    m_z += m_speedZ;
    setKm();
  } else {
    float RIGHT = CORRIDOR_WIDTH - m_radius;
    float TOP = CORRIDOR_HEIGHT - m_radius;
    m_x = posX > RIGHT ? RIGHT : posX < -RIGHT ? -RIGHT : posX;
    m_z = posY > TOP ? TOP : posY < -TOP ? -TOP : posY;
  }
}

void Ball::setMode() { m_mode = -m_mode; }

void Ball::setKm() { m_km += m_speedY; }

void Ball::setPos(char pos, float p) {
  switch (pos) {
  case 'X':
    m_x = p;
    break;
  case 'Y':
    m_y = p;
    break;
  case 'Z':
    m_z = p;
    break;
  default:
    break;
  }
}