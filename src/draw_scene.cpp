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

void drawTransparence(GLuint texture)
{
  // Activer la transparence
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Activer la texture
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  // Paramètres de la texture pour la transparence
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

};

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

/* ********** M E N U ********** */
void drawMenuCase(GLuint textureMenu)
{
  glPushMatrix();
    glColor3f(1, 1, 1);
    drawTexture(textureMenu);
    glTranslatef(16,-4,10);
    glScalef(0.5,0.5,1);
    glBegin(GL_QUADS);
  //ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
        glTexCoord3f(0,1,0);
        glVertex3d(-10,-10,-1);
        glTexCoord3f(1,1,0);
        glVertex3d(10,-10,-1);
        glTexCoord3f(1,0,0);
        glVertex3d(10,-10,1);
        glTexCoord3f(0,0,0);
        glVertex3d(-10,-10,1);
    glEnd();
    finTexture();
  glPopMatrix();
}

void drawMenu(GLuint textureMenu, GLuint textureJouer,GLuint textureNiveaux, GLuint textureQuitter){
  //texture Menu
  glPushMatrix();
  drawTexture(textureMenu);
  glTranslatef(0,0,8);
  glScalef(1,1,2);
  glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
      glTexCoord3f(0,1,0);
      glVertex3d(-10,-10,-1);
      glTexCoord3f(1,1,0);
      glVertex3d(10,-10,-1);
      glTexCoord3f(1,0,0);
      glVertex3d(10,-10,1);
      glTexCoord3f(0,0,0);
      glVertex3d(-10,-10,1);
    glEnd();
    finTexture();
  glPopMatrix();

  //texture Jouer
  glPushMatrix();
  drawTexture(textureJouer);
  glTranslatef(0,0,2);
  glScalef(0.8,1,1.5);
  glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
      glTexCoord3f(0,1,0);
      glVertex3d(-10,-10,-1);
      glTexCoord3f(1,1,0);
      glVertex3d(10,-10,-1);
      glTexCoord3f(1,0,0);
      glVertex3d(10,-10,1);
      glTexCoord3f(0,0,0);
      glVertex3d(-10,-10,1);
    glEnd();
    finTexture();
  glPopMatrix();

  //texture Niveaux
  glPushMatrix();
  drawTexture(textureNiveaux);
  glTranslatef(0,0,-2);
  glScalef(0.8,1,1.5);
  glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
      glTexCoord3f(0,1,0);
      glVertex3d(-10,-10,-1);
      glTexCoord3f(1,1,0);
      glVertex3d(10,-10,-1);
      glTexCoord3f(1,0,0);
      glVertex3d(10,-10,1);
      glTexCoord3f(0,0,0);
      glVertex3d(-10,-10,1);
    glEnd();
    finTexture();
  glPopMatrix();

  //texture Quitter
  glPushMatrix();
  drawTexture(textureQuitter);
  glTranslatef(0,0,-6);
  glScalef(0.8,1,1.5);
  glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
      glTexCoord3f(0,1,0);
      glVertex3d(-10,-10,-1);
      glTexCoord3f(1,1,0);
      glVertex3d(10,-10,-1);
      glTexCoord3f(1,0,0);
      glVertex3d(10,-10,1);
      glTexCoord3f(0,0,0);
      glVertex3d(-10,-10,1);
    glEnd();
    finTexture();
  glPopMatrix();

// Fond bleu
  glPushMatrix();
    glScalef(40,1,20);
    //glColor3f(0.4, 0.8, 1);
    glBegin(GL_QUADS);
      glVertex3f(-1.0,-10, -1.0);
      glVertex3f(-1.0,-10, 1.0);
      glVertex3f(1.0,-10, 1.0);
      glVertex3f(1.0, -10,-1.0);
    glEnd();
  glPopMatrix();

}

void drawNiveaux(GLuint textureNiveau1, GLuint textureNiveau2, GLuint textureRetour){
  glPushMatrix();
  drawTexture(textureNiveau1);
  glTranslatef(0,0,8);
  glScalef(0.8,1,1.5);
  glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
      glTexCoord3f(0,1,0);
      glVertex3d(-10,-10,-1);
      glTexCoord3f(1,1,0);
      glVertex3d(10,-10,-1);
      glTexCoord3f(1,0,0);
      glVertex3d(10,-10,1);
      glTexCoord3f(0,0,0);
      glVertex3d(-10,-10,1);
    glEnd();
    finTexture();
  glPopMatrix();

  glPushMatrix();
  drawTexture(textureNiveau2);
  glTranslatef(0,0,4);
  glScalef(0.8,1,1.5);
  glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
      glTexCoord3f(0,1,0);
      glVertex3d(-10,-10,-1);
      glTexCoord3f(1,1,0);
      glVertex3d(10,-10,-1);
      glTexCoord3f(1,0,0);
      glVertex3d(10,-10,1);
      glTexCoord3f(0,0,0);
      glVertex3d(-10,-10,1);
    glEnd();
    finTexture();
  glPopMatrix();

  glPushMatrix();
  drawTexture(textureRetour);
  glTranslatef(0,0,0);
  glScalef(0.8,1,1.5);
  glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
      glTexCoord3f(0,1,0);
      glVertex3d(-10,-10,-1);
      glTexCoord3f(1,1,0);
      glVertex3d(10,-10,-1);
      glTexCoord3f(1,0,0);
      glVertex3d(10,-10,1);
      glTexCoord3f(0,0,0);
      glVertex3d(-10,-10,1);
    glEnd();
    finTexture();
  glPopMatrix();

//Fond bleu
  glPushMatrix();
    glScalef(40,1,20);
    //
    //glColor3f(0.4, 0.8, 1);
    glBegin(GL_QUADS);
      glVertex3f(-1.0,-10, -1.0);
      glVertex3f(-1.0,-10, 1.0);
      glVertex3f(1.0,-10, 1.0);
      glVertex3f(1.0, -10,-1.0);
    glEnd();
  glPopMatrix();
}

void drawScoreCase(GLuint textureScoreCase, GLuint textureScore0, GLuint textureScore1, GLuint textureScore2, GLuint textureScore3, GLuint textureScore4, GLuint textureScore5){
  
  glPushMatrix();
  drawTexture(textureScoreCase);
  glTranslatef(13,-4,-19);
  glScalef(0.25*2,0.25*2,0.95*2);
  glBegin(GL_QUADS);
//ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
      glTexCoord3f(0,1,0);
      glVertex3d(-10,-10,-1);
      glTexCoord3f(1,1,0);
      glVertex3d(10,-10,-1);
      glTexCoord3f(1,0,0);
      glVertex3d(10,-10,1);
      glTexCoord3f(0,0,0);
      glVertex3d(-10,-10,1);
    glEnd();
    finTexture();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(18.2,-4,-20.4);
      glPushMatrix();
      drawTexture(textureScore0);
      glTranslatef(3.2,0,0);
      glScalef(2,2,2);
      glBegin(GL_QUADS);
    //ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
          glTexCoord3f(0,1,0);
          glVertex3d(-1,-1,-1);
          glTexCoord3f(1,1,0);
          glVertex3d(1,-1,-1);
          glTexCoord3f(1,0,0);
          glVertex3d(1,-1,1);
          glTexCoord3f(0,0,0);
          glVertex3d(-1,-1,1);
        glEnd();
        finTexture();
      glPopMatrix();
      
      glPushMatrix();
      drawTexture(textureScore1);
      glTranslatef(4.55*1.5,0,0);
      glScalef(2,2,2);
      glBegin(GL_QUADS);
    //ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
          glTexCoord3f(0,1,0);
          glVertex3d(-1,-1,-1);
          glTexCoord3f(1,1,0);
          glVertex3d(1,-1,-1);
          glTexCoord3f(1,0,0);
          glVertex3d(1,-1,1);
          glTexCoord3f(0,0,0);
          glVertex3d(-1,-1,1);
        glEnd();
        finTexture();
      glPopMatrix();

      glPushMatrix();
      drawTexture(textureScore2);
      glTranslatef(5.9*1.7,0,0);
      glScalef(2,2,2);
      glBegin(GL_QUADS);
    //ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
          glTexCoord3f(0,1,0);
          glVertex3d(-1,-1,-1);
          glTexCoord3f(1,1,0);
          glVertex3d(1,-1,-1);
          glTexCoord3f(1,0,0);
          glVertex3d(1,-1,1);
          glTexCoord3f(0,0,0);
          glVertex3d(-1,-1,1);
        glEnd();
        finTexture();
      glPopMatrix();
      
      glPushMatrix();
      drawTexture(textureScore3);
      glTranslatef(7.25*1.85,0,0);
      glScalef(2,2,2);
      glBegin(GL_QUADS);
    //ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
          glTexCoord3f(0,1,0);
          glVertex3d(-1,-1,-1);
          glTexCoord3f(1,1,0);
          glVertex3d(1,-1,-1);
          glTexCoord3f(1,0,0);
          glVertex3d(1,-1,1);
          glTexCoord3f(0,0,0);
          glVertex3d(-1,-1,1);
        glEnd();
        finTexture();
      glPopMatrix();

      glPushMatrix();
      drawTexture(textureScore4);
      glTranslatef(8.6*1.95,0,0);
      glScalef(2,2,2);
      glBegin(GL_QUADS);
    //ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
          glTexCoord3f(0,1,0);
          glVertex3d(-1,-1,-1);
          glTexCoord3f(1,1,0);
          glVertex3d(1,-1,-1);
          glTexCoord3f(1,0,0);
          glVertex3d(1,-1,1);
          glTexCoord3f(0,0,0);
          glVertex3d(-1,-1,1);
        glEnd();
        finTexture();
      glPopMatrix();
      
      glPushMatrix();
      drawTexture(textureScore5);
      glTranslatef(9.95*2,0,0);
      glScalef(2,2,2);
      glBegin(GL_QUADS);
    //ajouter un z sinon à cause du zbuffer ça se dessine derrière tout
          glTexCoord3f(0,1,0);
          glVertex3d(-1,-1,-1);
          glTexCoord3f(1,1,0);
          glVertex3d(1,-1,-1);
          glTexCoord3f(1,0,0);
          glVertex3d(1,-1,1);
          glTexCoord3f(0,0,0);
          glVertex3d(-1,-1,1);
        glEnd();
        finTexture();
      glPopMatrix();
  glPopMatrix();
}