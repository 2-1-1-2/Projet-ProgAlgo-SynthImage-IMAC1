#include "../include/draw_scene.h"
#include "../include/3D_tools.h"
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

// Repère 3D
void drawFrame() {
  glBegin(GL_LINES);
  // ligne y, rouge
  glColor3f(1, 0, 0);
  glVertex3f(0, 10, 0);
  glVertex3f(0, -10, 0);
  glColor3f(0.8, 0, 0);
  glVertex3f(0, 10, 0);
  glVertex3f(0, 15, 0);
  // ligne x, vert
  glColor3f(0, 1, 0);
  glVertex3f(10, 0, 0);
  glVertex3f(-10, 0, 0);
  glColor3f(0, 1, 1);
  glVertex3f(15, 0, 0);
  glVertex3f(10, 0, 0);
  // ligne z, bleu
  glColor3f(0, 0, 1);
  glVertex3f(0, 0, 10);
  glVertex3f(0, 0, -10);
  glColor3f(0, 1, 1);
  glVertex3f(0, 0, 15);
  glVertex3f(0, 0, 10);
  glEnd();
}

void drawTransparence() 
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_CULL_FACE);
  glColor4f(0.2, 0.2, 0.2, 0.9);
}

GLuint loadTexture(const char *fileName) 
{
  int x, y, n;
  unsigned char *image;
  image = stbi_load(fileName, &x, &y, &n, 0);
  if (image == NULL)
    printf("erreur");

  GLuint texture;
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE,
               image);
  stbi_image_free(image);
  return texture;
}

void drawTexture(GLuint texture) 
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void finTexture() 
{
  //glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

void deleteTexture(GLuint texture) 
{
  glDeleteTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, 0);
}