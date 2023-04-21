#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void drawFrame();

void drawBase();

void drawArm();

void drawPan();

void drawCorridor();

void drawLines();

void drawObstacle();

void drawBall();

void drawTexture();
GLuint loadTexture(const char* fileName);
void drawTexture(GLuint texture);
void deleteTexture();

void drawTransparence();

void drawMenu();
