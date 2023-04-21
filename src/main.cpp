#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "3D_tools.h"
#include "draw_scene.h"
#include "corridor.h"
#include "racket.h"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1280;
static const unsigned int WINDOW_HEIGHT = 720;
static const char WINDOW_TITLE[] = "Super jeu de la mort qui tue";
static float aspectRatio = 1.0;
static float GL_VIEW_SIZE = 21.5;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* IHM flag */
static int flag_walk = 0;
float walk = 0;
double posX = 0, posY = 0;

/* Error handling function */
void onError(int error, const char *description)
{
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
		switch (key)
		{
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

	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			flag_walk = 0;
			break;
		default:
			fprintf(stdout, "Touche non gérée (%d)\n", key);
		}
	}
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{

	glfwGetCursorPos(window, &posX, &posY);
	int windowTopLeftX = 0;
	int windowTopLeftY = 0;
	glfwGetWindowPos(window, &windowTopLeftX, &windowTopLeftY);

	// posX = (posX / (WINDOW_WIDTH / GL_VIEW_SIZE) - (0.5 * GL_VIEW_SIZE)) * fmax(aspectRatio, 1);
	// posY = -1 * (posY / (WINDOW_HEIGHT / GL_VIEW_SIZE) - (0.5 * GL_VIEW_SIZE)) * fmax(1 / aspectRatio, 1);
	posX = (25. / WINDOW_HEIGHT) * (posX - (WINDOW_WIDTH / 2));
	posY = -(25. / WINDOW_HEIGHT) * (posY - (WINDOW_HEIGHT / 2));

	printf("X : %f / Y : %f , aspect ratio %f \n", posX, posY, aspectRatio);
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

	// callback function
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	/* ********** INIT ********** */

	Corridor corridor(25, 60, 12, 1);
	Racket racket(2.5, -10, 2.5);

	/* ********** L O O P ********** */
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
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
		racket.drawRacket();

		/* Scene rendering */

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if (elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
		}

		/* Animate scenery */
	}

	glfwTerminate();
	return 0;
}
