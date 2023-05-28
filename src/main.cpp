#define GLFW_INCLUDE_NONE
#include "../include/3D_tools.h"
#include "../include/ball.h"
#include "../include/corridor.h"
#include "../include/draw_scene.h"
#include "../include/game.h"
#include "../include/racket.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "enemy.h"
#include <fstream>
#include <SOIL.h>
#include <sstream>
#include "struct.h"
#include <cstdlib>
#include <ctime> 


/* Window properties */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;
static const char WINDOW_TITLE[] = "Super jeu de la mort qui tue";
static float aspectRatio = 1;

/* Test position*/
static const float GL_VIEW_SIZE = 1.;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* IHM flag */
static int flag_walk = 0;
float alpha = 60;
static Game game(Ball(0., DISTANCE - 4, 0.), Corridor(25, alpha, 12, 1),
                 Racket(0., DISTANCE - 5, 0));
float walk = 0;
double posX = 0, posY = 0;
float h = -tan(toRad(alpha / 2.)) * 3 * DISTANCE;

/* Error handling function */
void onError(int error, const char *description) {
  fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow *window, int width, int height) 
{
  aspectRatio = width / (float)height;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, aspectRatio, Z_NEAR, Z_FAR);
  glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int scancode, int action, int mods) 
{
  if (action == GLFW_PRESS) 
  {
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
    default:
      fprintf(stdout, "Touche non gérée (%d)\n", key);
    }
  }

  if (action == GLFW_RELEASE) 
  {
    switch (key) 
    {
      default:
      fprintf(stdout, "Touche non gérée (%d)\n", key);
    }
  }
}

static void cursor_position_callback(GLFWwindow *window, double xpos,
                                     double ypos) 
{
  float r_l = game.getRacket().getLength();
  // TODO décalage sur les bords pour que ça ne sorte pas
  posX = xpos * ((h * aspectRatio) / WINDOW_WIDTH) - ((h * aspectRatio) / 2);
  posY = (-ypos * (h / WINDOW_HEIGHT) + (h / 2));
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) 
{
  switch (button) 
  {
    /* ***** W A L K ***** */
    case GLFW_MOUSE_BUTTON_LEFT:
      flag_walk = action == GLFW_PRESS ? 1 : 0;
    case GLFW_MOUSE_BUTTON_RIGHT:
      if (action == GLFW_PRESS && game.getBall().getMode() == 1)
        game.getBall().setMode();
      break;

    default:
      fprintf(stdout, "Touche non gérée (%d)\n", button);
  }
}

void readFile(std::string nameFile, std::vector<ImgTexture>& v_texture, int start, int end)
{
  std::string line;
  std::ifstream file(nameFile);

  if (!file.is_open())
    perror("error while opening file\n");

  v_texture.clear();

  GLuint img;
  std::string t;
  int format, rot;
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  int lineNumber = 0; 
  ColorRGB color(r, g, b);

  while (std::getline(file, line) && start < end) 
  {
    if(lineNumber >= start)
    {
      std::istringstream iss(line);
          
      if (!(iss >> t >> format >> rot) && !(iss >> t >> format >> rot >> r >> g >> b)) 
        perror("not the good number of elements");

      // jpg
      if(format == 0)
        img = loadTexture(t.c_str());
      else
      // png
      {
        img = SOIL_load_OGL_texture(t.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
      }

      GLenum error = glGetError();
      if (error != GL_NO_ERROR) 
      {
        // Il y a eu une erreur OpenGL lors du chargement de la texture
        const char* errorMessage = reinterpret_cast<const char*>(gluErrorString(error));
        fprintf(stderr, "Erreur OpenGL lors du chargement de la texture : %s n°%d\n", errorMessage, start); 
      }

      v_texture.push_back(ImgTexture{img, color, rot});

      start++;
    }
    lineNumber++;
  }
    
  if (file.bad())
    perror("error while reading file");

  file.close();
}

int main(int argc, char **argv) 
{
  /* GLFW initialisation */
  GLFWwindow *window;
  if (!glfwInit())
    return -1;

  /* Callback to a function if an error is rised by GLFW */
  glfwSetErrorCallback(onError);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
  if (!window) 
  {
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

  /* ********** I N I T ********** */
  srand(static_cast<unsigned int>(time(nullptr)));
  std::vector<ImgTexture> v_texture;
  std::vector<Enemy> v_enemys;
  readFile("src/loadImg.txt", v_texture, 0, 8);
  game.getCorridor().loadEnemys(v_enemys);
  

  /* ********** L O O P ********** */
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) 
  {
    /* Get time (in second) at loop beginning */
    double startTime = glfwGetTime();

    if (flag_walk) 
    {
      game.getCorridor().setWalk();
      //game.getRacket().setMode();
    }

    /* ***** R A C K E T ***** */
    game.getRacket().setPos(posX, posY);
    game.getBall().move(posX, posY);
    game.getBall().gameOver(game.getRacket());
    /* Cleaning buffers and setting Matrix Mode */
    glClearColor(0.2, 0.0, 0.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    setCamera();

    /* Initial scenery setup */
    drawFrame();

    /* ***** C O R R I D O R ***** */
    game.getCorridor().drawCorridor(v_texture);
    game.getCorridor().drawLines(v_enemys, v_texture);
    
    glPushMatrix();
      game.getRacket().drawRacket();
    glPopMatrix();

    glPushMatrix();
      // On dessine la balle
      drawTexture(v_texture[0].img);
      drawTransparence();

      glTranslatef(game.getBall().getPos('X'), game.getBall().getPos('Y'),
                   game.getBall().getPos('Z'));
      game.getBall().drawBall();
      finTexture();
    glPopMatrix();
    game.getBall().collision(game.getCorridor(), game.getRacket());
    // printf("TOUCHE ? %d\n",
    // game.getBall().collisionRacket(game.getRacket()));

    /* Scene rendering */

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    /* Elapsed time computation from loop begining */
    double elapsedTime = glfwGetTime() - startTime;
    /* If to few time is spend vs our wanted FPS, we wait */
    if (elapsedTime < FRAMERATE_IN_SECONDS)
      glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);

    /* Animate scenery */
  }

  /* ***** D E L E T E ***** */
  for (auto texture : v_texture) {
    deleteTexture(texture.img);
  }

  v_enemys.clear();

  glfwTerminate();
  return 0;
}
