#define GLFW_INCLUDE_NONE
#include "../include/3D_tools.h"
#include "../include/ball.h"
#include "../include/corridor.h"
#include "../include/draw_scene.h"
#include "../include/enemy.h"
#include "../include/game.h"
#include "../include/racket.h"
#include "../include/struct.h"
#include "../include/bonus.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "menu.h"
#include <cmath>

/* Window properties */
static const char WINDOW_TITLE[] = "Super jeu de la mort qui tue";
static float aspectRatio = 1;

static unsigned int WINDOW_WIDTH = 1920;
static unsigned int WINDOW_HEIGHT = 1080;

/* Test position*/
static const float GL_VIEW_SIZE = 1.;
/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* IHM flag */
static int flag_walk = 0;
static Game game(Ball(0., DISTANCE / 5 + RADIUS_CIRCLE, 0.),
                 Corridor(CORRIDOR_WIDTH, FOCAL, CORRIDOR_HEIGHT, 0.3f),
                 Racket(0., DISTANCE / 5 + 1, 0));

double posX = 0, posY = 0;
float h = tan(toRad(FOCAL / 2.)) * (DISTANCE);

/* Error handling function */
void onError(int error, const char *description) {
  fprintf(stderr, "GLFW Error: %s\n", description);
}

void score(float score, int (&arr)[6])
{
  arr[0] = round(score/100000.0f);
  arr[1] = fmodf(score/10000.0f, 10.0f);
  arr[2] = fmodf(score/1000.0f, 10.0f);
  arr[3] = fmodf(score/100.0f, 10.0f);
  arr[4] = fmodf(score/10.0f, 10.0f);
  arr[5] = fmodf(score, 10.0f);
}

void onWindowResized(GLFWwindow *window, int width, int height) 
{
  WINDOW_WIDTH = width;   // AJOUTER ICI
  WINDOW_HEIGHT = height; // AJOUTER ICI
  aspectRatio = width / (float)height;

  h = tan(toRad(FOCAL / 2.)) * (DISTANCE);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOCAL, aspectRatio, Z_NEAR, Z_FAR);
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
    default:
      fprintf(stdout, "Touche non gérée (%d)\n", key);
      break;
    }
  }

  if (action == GLFW_RELEASE) {
    switch (key) {
    default:
      fprintf(stdout, "Touche non gérée (%d)\n", key);
      break;
    }
  }
}

static void cursor_position_callback(GLFWwindow *window, double xpos,
                                     double ypos) {
  float r_l = game.getRacket().getLength();
  // TODO décalage sur les bords pour que ça ne sorte pas

  posX = -((xpos * 2 / WINDOW_WIDTH) - 1) * aspectRatio;
  posY = ((ypos * 2 / WINDOW_HEIGHT) - 1);

  posX = xpos * ((h * aspectRatio) / WINDOW_WIDTH) - ((h * aspectRatio));

  posY = (ypos * (h / WINDOW_HEIGHT) + (h / 2));

  // posY = posY * tan(((FOCAL * M_PI) / 180) / 2) * DISTANCE / 5 / aspectRatio;
  // posX = posX * tan(((FOCAL * M_PI) / 180) / 2) * DISTANCE / 5 / aspectRatio;

  posY = (((ypos * 2 / WINDOW_HEIGHT) - 1)) * toRad(FOCAL / 2.) * DISTANCE;

  posX = -(((xpos * 2 / WINDOW_WIDTH) - 1) * aspectRatio) * toRad(FOCAL / 2.) *
         DISTANCE;

  //printf("POSX %f POSY %f\n", posX, posY);
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  switch (button) 
  {
    /* ***** W A L K ***** */
    case GLFW_MOUSE_BUTTON_LEFT:
      // si le bouton est pressé et que la balle est en mouvement
      if(action == GLFW_PRESS)
      {
        printf("AU MOINS JE SUIS PRESSE!\n");
        if(game.getMenu().getMenu())
        {
          if (posX >= -8.915609 && posX <= 9.018680)
          {
            // Jouer
            if(posY >= 0.669959 && posY <= 3.813613)
            {
              game.getMenu().setType(0);
              game.getMenu().setMenu(false);
            }
            // Niveaux
            if(posY >= -3.813613 && posY <= -0.773030)
              game.getMenu().setType(1);
            // Quitter
            if(posY >= -8.451791 && posY <= -5.153531)
              glfwSetWindowShouldClose(window, GLFW_TRUE);
          }
        }
        else if(game.getBall().getMode() == -1)
        {
          flag_walk = 1;
        }
      }
      else if (action == GLFW_RELEASE)
        flag_walk = 0;
      break;
    case GLFW_MOUSE_BUTTON_RIGHT:
      if (action == GLFW_PRESS && game.getBall().getMode() == 1)
      {
        game.getBall().setMode();
        if(game.getLose())
          game.setLose(false);
      }
      break;

    default:
      fprintf(stdout, "Touche non gérée (%d)\n", button);
      break;
  }
}

void readFile(std::string nameFile, std::vector<ImgTexture> &v_texture,
              int start, int end) {
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

  while (std::getline(file, line) && start < end) {
    if (lineNumber >= start) {
      std::istringstream iss(line);

      if (!(iss >> t >> format >> rot) &&
          !(iss >> t >> format >> rot >> r >> g >> b))
        perror("not the good number of elements");

      // jpg
      if (format == 0)
        img = loadTexture(t.c_str());
      else
      // png
        img = SOIL_load_OGL_texture(t.c_str(), SOIL_LOAD_AUTO,
                                    SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

      GLenum error = glGetError();
      if (error != GL_NO_ERROR) {
        // Il y a eu une erreur OpenGL lors du chargement de la texture
        const char *errorMessage =
            reinterpret_cast<const char *>(gluErrorString(error));
        fprintf(stderr,
                "Erreur OpenGL lors du chargement de la texture : %s n°%d\n",
                errorMessage, start);
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
  glEnable(GL_BLEND);
  //initLight();

  /* ********** I N I T I A L I S A T I O N ********** */
  srand(static_cast<unsigned int>(time(nullptr)));
  std::vector<ImgTexture> v_texture;
  std::vector<Enemy> v_enemys;
  std::vector<Bonus> v_bonus;

  readFile("src/loadImg.txt", v_texture, 0, 10);
  game.getCorridor().loadEnemys(v_enemys);
  game.getCorridor().loadBonus(v_bonus);

  /* *********** I N I T     N I N A ********** */
  GLuint textureMenu = loadTexture("img/menu/principal/menu.jpg");
  GLuint textureJouer = loadTexture("img/menu/principal/jouer.jpg");
  GLuint textureNiveaux = loadTexture("img/menu/principal/niveaux.jpg");
  GLuint textureQuitter = loadTexture("img/menu/principal/quitter.jpg");

  //Load texture Niveaux
  GLuint textureNiveau1 = loadTexture("img/menu/niveaux/niveau1.jpg");
  GLuint textureNiveau2 = loadTexture("img/menu/niveaux/niveau2.jpg");
  GLuint textureNiveau3 = loadTexture("img/menu/niveaux/niveau3.jpg");
  GLuint textureNiveau4 = loadTexture("img/menu/niveaux/niveau4.jpg");
  GLuint textureNiveau5 = loadTexture("img/menu/niveaux/niveau5.jpg");

  // score
  GLuint textureScoreCase = loadTexture("img/menu/score/textureScoreCase.jpg");
  int arr[6] = {0};
  const int nombreTexture = 10;
  const char* cheminTexture[nombreTexture] = {"img/menu/score/textureScore0.jpg", "img/menu/score/textureScore1.jpg", "img/menu/score/textureScore2.jpg", "img/menu/score/textureScore3.jpg","img/menu/score/textureScore4.jpg","img/menu/score/textureScore5.jpg", "img/menu/score/textureScore6.jpg", "img/menu/score/textureScore7.jpg","img/menu/score/textureScore8.jpg","img/menu/score/textureScore9.jpg"};

  printf("AVANT LA BOUCLE\n");


  /* Loop until the user closes the window */
  /* ***************** L O O P     G A M E ******************** */
  while (!glfwWindowShouldClose(window)) 
  {
    double startTime = glfwGetTime();

    /* Cleaning buffers and setting Matrix Mode */
    glClearColor(0., 0.0, 0.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    setCamera();

    /* Initial scenery setup */
    drawFrame();

    /* ********************* M   E   N   U ********************** */
    if(game.getMenu().getMenu())
    {
      glDisable(GL_LIGHTING);
      //printf("LE MENU: %d\n", game.getMenu().getType());
      switch (game.getMenu().getType()) 
      {
        case 0:
            //printf("DANS LE MENU ZERO\n");
            drawMenu(textureMenu, textureJouer, textureNiveaux, textureQuitter);
            break;
        case 1:
          printf("DANS LE MENU UN\n");
          drawNiveaux(textureNiveau1, textureNiveau2, textureNiveau3, textureNiveau4, textureNiveau5);
          break;
      }
    }
    /* ******************************** G A M E ************************************ */
    else
    {
      GLuint textureScore0 = loadTexture(cheminTexture[arr[0]]);
      GLuint textureScore1 = loadTexture(cheminTexture[arr[1]]);
      GLuint textureScore2 = loadTexture(cheminTexture[arr[2]]);
      GLuint textureScore3 = loadTexture(cheminTexture[arr[3]]);
      GLuint textureScore4 = loadTexture(cheminTexture[arr[4]]);
      GLuint textureScore5 = loadTexture(cheminTexture[arr[5]]);

      if (flag_walk) 
      {
        printf("JE VEUX RENTRER\n");
        game.getCorridor().setWalk();
        game.setScore();
        // game.getRacket().setMode();
      }

      //printf("LE SCORE %f\n", game.getScore());

      /* ***** R A C K E T ***** */
      /*game.getRacket().setPos(posX, posY);
      game.getBall().move(posX, posY);*/
      game.collision(v_enemys, posX, posY, flag_walk);
      if(game.getCollisionRacket())
      {
        // Le joueur a perdu
        if(game.getLose())
          flag_walk = 0;
        // Si le joueur n'a pas perdu et qu'il a le bonus colle
        else if(!game.getLose() && game.getGlue())
          game.setGlue(false);
      }

      if(game.gameOver())
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      

      /* ***** B O N U S ***** */
      game.isThereBonus(v_bonus);
      /* ****************************** D R A W I N G ****************************** */
      game.getCorridor().drawCorridor(v_texture);
      game.getCorridor().drawLines(v_enemys, v_bonus, v_texture);
      game.drawBonus(v_texture);
      drawMenuCase(textureMenu);
      drawScoreCase(textureScoreCase, textureScore0, textureScore1, textureScore2, textureScore3, textureScore4, textureScore5);

      /* ALED */
      score(game.getScore(), arr);
      //printf("TA RACE %f %d\n", game.getScore(), arr[2]);


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

      // S'il y a collision avec la raquette
      /*if(game.getBall().collision(game.getCorridor(), game.getRacket(), game.getGlue()))
      {
        // Le joueur a perdu
        /*if(game.getLose())
          flag_walk = 0;
        // Si le joueur n'a pas perdu et qu'il a le bonus colle
        else if(!game.getLose() && game.getGlue())
          game.setGlue(false);*/
      //}
      // printf("TOUCHE ? %d\n",
      // game.getBall().collisionRacket(game.getRacket()));

      // game.getBall().collision(game.getCorridor(), game.getRacket(), v_enemys);
      //  printf("TOUCHE ? %d\n",
      //  game.getBall().collisionRacket(game.getRacket()));
    }

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

  deleteTexture(textureMenu);
  deleteTexture(textureJouer);
  deleteTexture(textureNiveaux);
  deleteTexture(textureScoreCase);
  deleteTexture(textureQuitter);
  deleteTexture(textureNiveau1);
  deleteTexture(textureNiveau2);
  deleteTexture(textureNiveau3);
  deleteTexture(textureNiveau4);
  deleteTexture(textureNiveau5);

  v_enemys.clear();
  v_bonus.clear();

  glfwTerminate();
  return 0;
}
