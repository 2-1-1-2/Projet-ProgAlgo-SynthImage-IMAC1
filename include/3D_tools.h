#pragma once
#define NB_SEG_CIRCLE 64
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

/* Camera parameters and functions */
static const float Z_NEAR = 0.1f;
static const float Z_FAR = 100.f;
extern float theta;      // Angle between x axis and viewpoint
extern float phy  ;      // Angle between z axis and viewpoint
extern float dist_zoom ; // Distance between origin and viewpoint
extern float walk;

void setCamera();

/* Draw cannonic objet functions */
void drawEnemy(int x1, int x2, int y, int z1, int z2);
void drawHorizontalEnemy(int x, int y, int z1, int z2);
void drawVerticalEnemy(int x1, int x2, int y, int z);
void drawSquare(int x, int y, int z, int start, bool vertical);

void drawLineLoop(int x, int y, int z);

void drawCircle();

void drawCone();

void drawSphere();

/* Small tools */
float toRad(float deg);
