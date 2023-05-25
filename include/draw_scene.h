#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void drawFrame();

void drawBall();

GLuint loadTexture(const char *fileName);
void drawTexture(GLuint texture);
void finTexture();
void deleteTexture(GLuint texture);

void drawTransparence();