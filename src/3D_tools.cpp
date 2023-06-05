#include "../include/3D_tools.h"
#include <GL/gl.h>

void setCamera() {
  gluLookAt(0, DISTANCE, 0.0, // origin cam
            0.0, 0.0, 0.0,    // point regardé
            0.0, 0.0, 1.0);   // orientation
}
/* Convert degree to radians */
float toRad(float deg) { return deg * M_PI / 180.0f; }

void drawEnemy(int x1, int x2, int y, int z1, int z2) {
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(x1, y, z1);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x2, y, z1);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x2, y, z2);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(x1, y, z2);
  glEnd();
}

void drawHorizontalEnemy(int x, int y, int z1, int z2) {
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-x, y, z1);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(x, y, z1);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(x, y, z2);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-x, y, z2);
  glEnd();
}

void drawVerticalEnemy(int x1, int x2, int y, int z, bool rot) {
  // right side up
  if (rot) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, y, -z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x2, y, -z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x2, y, z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y, z);
    glEnd();
  } else {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y, -z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x2, y, -z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x2, y, z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x1, y, z);
    glEnd();
  }
}

void drawSquare(int x, int y, int z, int start, bool vertical) {
  if (vertical) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-x, start, z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, start, z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-x, y, z);
    glEnd();
  } else {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, start, z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x, y, -z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, start, -z);
    glEnd();
  }
}

void drawLineLoop(int x, int y, int z) {
  glBegin(GL_LINE_LOOP);
  glVertex3f(-x + 0.1, y, -z + 0.1);
  glVertex3f(x - 0.1, y, -z + 0.1);
  glVertex3f(x - 0.1, y, z);
  glVertex3f(-x + 0.1, y, z);
  glEnd();
}

void drawCircle() {
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0, 0.0, 0.0);
  float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
  for (int i = 0; i <= NB_SEG_CIRCLE; i++) {
    glVertex3f(cos(i * step_rad), sin(i * step_rad), 0.0f);
  }
  glEnd();
}

void drawCone() {
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0, 0.0, 1.0);
  float step_rad = 2 * M_PI / (float)NB_SEG_CIRCLE;
  for (int i = 0; i <= NB_SEG_CIRCLE; i++) {
    glVertex3f(cos(i * step_rad), sin(i * step_rad), 0.0f);
  }
  glEnd();
}

void drawSphere() {
  gluSphere(gluNewQuadric(), 1.0, NB_SEG_CIRCLE, NB_SEG_CIRCLE);
}

void light() {
  GLfloat ambiantColor[] = {1.f, 1.f, 1.f, 1.f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiantColor);

  // Position

  GLfloat lightColor0[] = {1.f, 1.f, 1.f, 1.f};
  GLfloat lightPos0[] = {0.f, 0.f, -15.f, 1.f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

  GLfloat lightColor1[] = {1.f, 1.f, 1.f, 1.f};

  GLfloat lightPos1[] = {0.f, -1.f, 0.f, 1.f}; // partant en direection

  // glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
  // glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
}
void initLight() {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  light();
}
