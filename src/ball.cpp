#include "../include/ball.h"

Ball::Ball(float x, float y, float z) {
  m_x = x;
  m_y = y;
  m_z = z;
  m_size = 32;
  m_speedX = 0;
  m_speedY = 0.4;
  m_radius = RADIUS_CIRCLE;
  m_speedZ = 0;
  m_mode = 1; // 1 sticky, -1 rebond
}

/* ********** F U N C T I O N S ********** */
void Ball::drawBall() {

  static GLfloat vCompColor[4];
  vCompColor[0] = 1.;
  vCompColor[1] = 1.;
  vCompColor[2] = 1.;
  vCompColor[3] = 1.f;
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, vCompColor);
  glMaterialfv(GL_FRONT, GL_SPECULAR, vCompColor);

  glColor3f(1, 1, 1);
  GLUquadricObj *quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  // gluDeleteQuadric(quadric);
  gluSphere(quadric, m_radius, m_size, m_size);
}

int Ball::collisionRacket(
    Racket r, bool glue,
    bool *collision_racket) { // 0 collision, 1 collision, -1 perdu une vie
  // On vérifie si c'est sur le même Y
  if (m_y > r.getPos('Y') - m_radius)
    return 0;
  float d_x = r.getPos('X') - m_x;
  float d_z = r.getPos('Z') - m_z;
  if (abs(d_x) - m_radius * 2 > r.getLength() || m_y < DISTANCE / 5 - 1) {

    setPos('X', r.getPos('X'));
    setPos('Z', r.getPos('Z'));
    setMode();
    return -1;
  }
  // Bonus de colle
  if (glue && m_mode != 1)
    m_mode = -m_mode;
  else {
    m_speedX = (d_x) / (r.getLength() * 5.);
    m_speedZ = (d_z) / (r.getLength() * 5.);
    // m_y += r.getLength();

    m_speedY = m_y < 0 ? abs(m_speedY) : -abs(m_speedY);

    m_y += m_speedY;
  }
  *collision_racket = true;
  return 1;
}

int Ball::collisionCorridor(Corridor c) {
  // On vérifie si c'est sur le même Y
  int res = 0; // 0 rien, 1 GD, 2 HB, 3 GBHB

  if (abs(m_x) + m_radius > abs(c.getPos('X'))) {

    m_speedX = m_x < 0 ? abs(m_speedX) : -abs(m_speedX);
    res += 1;
  }
  if (abs(m_z) + m_radius > abs(c.getPos('Z'))) {

    m_speedZ = m_z < 0 ? abs(m_speedZ) : -abs(m_speedZ);
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
    if (abs(element.getD() - m_y) > RADIUS_CIRCLE)
      continue;

    if (element.contains(m_x, m_z, cx, cz)) {

      m_speedY = element.getD() < m_y ? abs(m_speedY) : -abs(m_speedY);
      m_y += m_speedY;
      printf("collision mur ennemie d%f m_y%f m_speedY%f  \n", element.getD(),
             m_y, m_speedY);
      return true;
    }
  }
  return false;
}

int Ball::collision(Corridor c, Racket r, std::vector<Enemy> v_enemys,
                    bool glue, bool *collision_racket) {
  *collision_racket = false;
  return (collisionCorridor(c) || collisionRacket(r, glue, collision_racket) ||
          collisionEnemy(v_enemys, c.getPos('X') - m_radius * 2,
                         c.getPos('Z') - m_radius * 2));
}

/* ********** G E T T E R S ********** */
float Ball::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}

int Ball::getMode() { return m_mode; }

/* ********** S E T T E R S ********** */
void Ball::move(float posX, float posY) {
  if (m_mode == -1) {
    m_x += m_speedX;
    m_y += m_speedY;
    m_z += m_speedZ;
  } else {
    float RIGHT = CORRIDOR_WIDTH - m_radius;
    float TOP = CORRIDOR_HEIGHT - m_radius;
    m_x = posX > RIGHT ? RIGHT : posX < -RIGHT ? -RIGHT : posX;
    m_z = posY > TOP ? TOP : posY < -TOP ? -TOP : posY;
  }
}

void Ball::setMode() { m_mode = -m_mode; }

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