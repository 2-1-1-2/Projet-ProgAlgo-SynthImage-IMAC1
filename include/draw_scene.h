#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void drawFrame();
void drawTransparence(GLuint texture);
void drawTransparence();

GLuint loadTexture(const char *fileName);
void drawTexture(GLuint texture);
void finTexture();
void deleteTexture(GLuint texture);

void drawTransparence();

/* ********** MENU ********** */
void drawMenuCase(GLuint textureMenu);
void drawMenu(GLuint textureMenu, GLuint textureJouer,GLuint textureNiveaux, GLuint textureQuitter);
void drawNiveaux(GLuint textureNiveau1, GLuint textureNiveau2, GLuint textureRetour);
void drawScoreCase(GLuint textureScoreCase, GLuint textureScore0, GLuint textureScore1, GLuint textureScore2, GLuint textureScore3, GLuint textureScore4, GLuint textureScore5);
void drawScoreCaseFin(GLuint textureScoreCase, GLuint textureScore0,
                      GLuint textureScore1, GLuint textureScore2,
                      GLuint textureScore3, GLuint textureScore4,
                      GLuint textureScore5);

void drawFinJeu(GLuint textureFin, GLuint textureScore, GLuint textureScoreCase,
                GLuint textureScore0, GLuint textureScore1,
                GLuint textureScore2, GLuint textureScore3,
                GLuint textureScore4, GLuint textureScore5,
                GLuint textureRejouer, GLuint textureQuitter);
