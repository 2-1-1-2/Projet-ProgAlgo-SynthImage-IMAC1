#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_SEG_CIRCLE 64
#define RADIUS_CIRCLE 1.5
#define CORRIDOR_WIDTH 25
#define CORRIDOR_HEIGHT 12
#define DISTANCE -50.
#define FOCAL 60.

/* Camera parameters and functions */
static const float Z_NEAR = 0.1f;
static const float Z_FAR = 100.f;
extern float theta;     // Angle between x axis and viewpoint
extern float phy;       // Angle between z axis and viewpoint
extern float dist_zoom; // Distance between origin and viewpoint
extern float walk;

void setCamera();

/* Draw cannonic objet functions */
void drawEnemy(int x1, int x2, int y, int z1, int z2);
void drawHorizontalEnemy(int x, int y, int z1, int z2);
void drawVerticalEnemy(int x1, int x2, int y, int z, bool rot);
void drawA(int x, float y, int z, int start, bool vertical);
void drawSquare(float x, float y, float z, float h, GLenum m_mode);

void drawLineLoop(int x, int y, int z);

void drawCircle();
void drawCircle(float x, float y, float z, float r);

void drawCone();

void drawSphere();

/* Small tools */
float toRad(float deg);
void light(); 
void initLight();