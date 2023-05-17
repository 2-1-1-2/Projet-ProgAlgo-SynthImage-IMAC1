#define GLFW_INCLUDE_NONE
#include "3D_tools.h"
#include "corridor.h"
#include "draw_scene.h"
#include "racket.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1280;
static const unsigned int WINDOW_HEIGHT = 720;
static const char WINDOW_TITLE[] = "Super jeu de la mort qui tue";
static float aspectRatio = 1;

/* Test position*/
static const float GL_VIEW_SIZE = 1.;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* IHM flag */
static int flag_walk = 0;
float walk = 0;
double posX = 0, posY = 0;
float distance = -10;
float h = 23; // tan(toRad(60 / 2.)) * 2 * distance;
Racket racket(0., -10., 0);

/* Error handling function */
void onError(int error, const char *description) {
  fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow *window, int width, int height) {
  aspectRatio = width / (float)height;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, aspectRatio, Z_NEAR, Z_FAR);
  glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_A:
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(window, GLFW_TRUE);
      break;
    case GLFW_KEY_L:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case GLFW_KEY_P:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
    /* *** FAIRE BOUGER LA CAMERA *** */
    case GLFW_KEY_UP:
      flag_walk = 1;
      break;
    default:
      fprintf(stdout, "Touche non gérée (%d)\n", key);
    }
  }

  if (action == GLFW_RELEASE) {
    switch (key) {
    case GLFW_KEY_UP:
      flag_walk = 0;
      break;
    default:
      fprintf(stdout, "Touche non gérée (%d)\n", key);
    }
  }
}

static void cursor_position_callback(GLFWwindow *window, double xpos,
                                     double ypos) {
  posX = xpos * ((h * aspectRatio) / WINDOW_WIDTH) - ((h * aspectRatio) / 2);
  posY = (-ypos * (h / WINDOW_HEIGHT) + (h / 2));
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    racket.setMode();
  }
}

int main(int argc, char **argv) {
  /* GLFW initialisation */
  GLFWwindow *window;
  if (!glfwInit())
    return -1;

  /* Callback to a function if an error is rised by GLFW */
  glfwSetErrorCallback(onError);

  /* Create a windowed mode window and its OpenGL context */
  window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
  if (!window) {
    // If no context created : exit !
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /*  callback function */
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetWindowSizeCallback(window, onWindowResized);
  glfwSetKeyCallback(window, onKey);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

  glPointSize(5.0);
  glEnable(GL_DEPTH_TEST);

  /* ********** INIT ********** */

  Corridor corridor(25, 60, 12, 1);

  /* ********** L O O P ********** */
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Get time (in second) at loop beginning */
    double startTime = glfwGetTime();

    if (flag_walk)
      corridor.setWalk();

    racket.setPos(posX, posY);
    /* Cleaning buffers and setting Matrix Mode */
    glClearColor(0.2, 0.0, 0.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    setCamera();

    /* Initial scenery setup */
    drawFrame();

    corridor.drawCorridor();

    corridor.drawLines();
    glPushMatrix();

    // glTranslatef(posX, 0, posY);
    racket.drawRacket();

    glPopMatrix();

    /* Scene rendering */

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    /* Elapsed time computation from loop begining */
    double elapsedTime = glfwGetTime() - startTime;
    /* If to few time is spend vs our wanted FPS, we wait */
    if (elapsedTime < FRAMERATE_IN_SECONDS) {
      glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
    }

    /* Animate scenery */
  }

  glfwTerminate();
  return 0;
}
