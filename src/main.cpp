#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <list>
#include "3D_tools.h"
#include "draw_scene.h"


//#include "stb_image.h"

/*Light*/
GLfloat light_position[] = { 0.0, -5.0, -5.0, 0.0 };  // Position de la lumière
GLfloat light_direction[] = { 0.0, 0.0, 1.0 };    // Direction de la lumière

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;
static const char WINDOW_TITLE[] = "Super jeu de la mort qui tue";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* IHM flag */
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;
int flag_walk = 0;
static float walk = 0;

// cursor position
double xpos, ypos;

//score 
int score = 0;

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,aspectRatio,Z_NEAR,Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}

bool menuItemSelected = false;
bool menu1=true;
bool jouerSelected = false;
bool niveauSelected = false;
bool niveau1Selected = false;
bool niveau2Selected = false;
bool niveau3Selected = false;
bool quitterSelected = false;
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) { 

        glfwGetCursorPos(window, &xpos, &ypos);
		fprintf(stdout, "Coordonnées du curseur : (%f, %f)\n", xpos, ypos);

		if(( xpos >= 590 && xpos <= 1330 && ypos >= 542 && ypos <= 675) ){
			menu1=false;
			menuItemSelected=false;
			niveauSelected = true;
		}
		if( (xpos >= 590 && xpos <= 1330 && ypos >= 353 && ypos <= 491)){
			menu1=false;
			menuItemSelected=false;
			jouerSelected = true;
		}
		if( (xpos >= 590 && xpos <= 1335 && ypos >= 72 && ypos <= 210)){
			menu1=false;
			menuItemSelected=false;
			niveauSelected=false;
			niveau1Selected = true;
		}
		if( (xpos >= 590 && xpos <= 1330 && ypos >= 728 && ypos <= 864) ){
			menu1=false;
			menuItemSelected=false;
			quitterSelected = true;
		}
		if((xpos >= 1462 && xpos <= 1893 && ypos >= 35 && ypos <= 110)){
			niveauSelected = false;
			niveau1Selected = false;
			jouerSelected = false;
			quitterSelected = false;
			menu1=false;
			menuItemSelected = true;
		}
		
    }
}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) 
	{
		switch(key) 
		{	
			
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			case GLFW_KEY_L :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			/* *** FAIRE BOUGER LA CAMERA *** */
			case GLFW_KEY_UP:
				flag_walk = 1;
				break;
			default: fprintf(stdout,"Touche non gérée (%d)\n",key);

			
			
		}
		
    }
	

	if (action == GLFW_RELEASE) 
	{
		switch(key) 
		{
			case GLFW_KEY_UP:
				flag_walk = 0;
				break;
			default: fprintf(stdout,"Touche non gérée (%d)\n",key);
			
		}
	}

}

int main(int argc, char** argv)
{
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

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
	
	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

    /*Light*/
	


	//Load texture Menu
	GLuint textureMenu = loadTexture("../doc/textureMenu.jpg");
	GLuint textureJouer = loadTexture("../doc/textureJouer.jpg");
	GLuint textureNiveaux = loadTexture("../doc/textureNiveaux.jpg");
	GLuint textureQuitter = loadTexture("../doc/textureQuitter.jpg");
	GLuint textureBall = loadTexture("../doc/textureBall.jpg");

	//Load texture Fin du jeu
	GLuint textureFin = loadTexture("../doc/textureFin.jpg");
	GLuint textureRejouer = loadTexture("../doc/textureRejouer.jpg");
	GLuint textureScore = loadTexture("../doc/textureScore.jpg");
	GLuint textureScoreCase = loadTexture("../doc/textureScoreCase.jpg");

	//Load texture Niveaux
	GLuint textureNiveau1 = loadTexture("../doc/textureNiveau1.jpg");
	GLuint textureNiveau2 = loadTexture("../doc/textureNiveau2.jpg");
	GLuint textureNiveau3 = loadTexture("../doc/textureNiveau3.jpg");
	GLuint textureNiveau4 = loadTexture("../doc/textureNiveau4.jpg");
	GLuint textureNiveau5 = loadTexture("../doc/textureNiveau5.jpg");

	// afficher le score, changement de texture en fonction du score

	int score = 0;
	int score0 = score/10;
	int score1 = score%10;
	const int nombreTexture = 10;
	const char* cheminTexture[nombreTexture] = {"../doc/textureScore0.jpg", "../doc/textureScore1.jpg", "../doc/textureScore2.jpg", "../doc/textureScore3.jpg","../doc/textureScore4.jpg","../doc/textureScore5.jpg", "../doc/textureScore6.jpg", "../doc/textureScore7.jpg","../doc/textureScore8.jpg","../doc/textureScore9.jpg"};
	GLuint textureScore0 = loadTexture(cheminTexture[score0]);
	GLuint textureScore1 = loadTexture(cheminTexture[score1]);



	

	/* ********** L O O P ********** */
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		if(flag_walk)
		

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();
		
		
		/* Initial scenery setup */
		glPushMatrix();
		glLoadIdentity();
		glPopMatrix();
		
		

		// Dev Menu
		glPushMatrix();
		glDisable(GL_LIGHTING);
		drawMenuCase(textureMenu);
		drawScoreCase(textureScoreCase, textureScore0, textureScore1);

		if (menu1){
			drawMenu(textureMenu, textureJouer, textureNiveaux, textureQuitter);
		}
		
		if (menuItemSelected) {
            drawMenu(textureMenu, textureJouer, textureNiveaux, textureQuitter); // Appeler la fonction de menu
		}
		if(niveauSelected){
			drawNiveaux(textureNiveau1, textureNiveau2, textureNiveau3, textureNiveau4, textureNiveau5);			
		}
		if(niveau1Selected){
			menuItemSelected= false;
			menu1=false;
			niveauSelected= false;
		}
		if(jouerSelected){ 
			menuItemSelected= false;
			menu1=false;
		}
		if(quitterSelected){
			menuItemSelected= false;
			menu1=false;
			glfwWindowShouldClose(window);
		}

	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
		GLfloat globalAmbientColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Couleur ambiante globale (RGB)
		GLfloat globalDiffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Couleur diffuse globale (RGB)
		GLfloat globalSpecularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Couleur spéculaire globale (RGB)
		GLfloat globalShininess = 90.0f; // Brillance globale du matériau

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, globalAmbientColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, globalDiffuseColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, globalSpecularColor);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, globalShininess);
		drawFrame();
		
		drawCorridor();
		
		drawLines();
		
		/* Scene rendering */


		glPushMatrix();
			glScalef(4,4,4);
			glRotated(90,1,0,0);
			glRotated(-25,0,1,0);
			glTranslatef(-4,0,2);
			drawTransparence();
			drawSquare();
		glPopMatrix();

		/*texture*/
		
		drawTexture(textureBall);
			drawBall();
		finTexture();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}

		/* Animate scenery */
	}
	
	deleteTexture(textureBall);
	deleteTexture(textureMenu);
	deleteTexture(textureJouer);
	deleteTexture(textureNiveaux);
	deleteTexture(textureFin);
	deleteTexture(textureRejouer);
	deleteTexture(textureScore);
	deleteTexture(textureQuitter);
	deleteTexture(textureNiveau1);
	deleteTexture(textureNiveau2);
	deleteTexture(textureNiveau3);
	deleteTexture(textureNiveau4);
	deleteTexture(textureNiveau5);

	glfwTerminate();
	
	return 0;
}
