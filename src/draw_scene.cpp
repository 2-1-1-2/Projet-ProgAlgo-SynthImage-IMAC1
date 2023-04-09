#include "draw_scene.h"
#include "3D_tools.h"
#include "math.h"

/*void drawArm() 
{
	// sphere
	glPushMatrix();
		glTranslatef(0.0, 0.0, 10);
		glPushMatrix();
			glColor3f(245.0/255.0, 164.0/255.0, 66.0/255.0);
			glScalef(1.5, 1.5, 1.5);
			drawSphere();
		glPopMatrix();

		// cone 1
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glScalef(1.0,1.0,10.0);
			drawCone();
		glPopMatrix();

		// cone 2
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glScalef(1.0,1.0,10.0);
			drawCone();
		glPopMatrix();
	glPopMatrix();
}*/

// Repère 3D
void drawFrame() 
{
	glBegin(GL_LINES);
		//ligne y, rouge
		glColor3f(1, 0, 0);
		glVertex3f(0, 10, 0);
		glVertex3f(0, -10, 0);
		glColor3f(0.8, 0, 0);
		glVertex3f(0, 10, 0);
		glVertex3f(0, 15, 0);
		//ligne x, vert
		glColor3f(0, 1, 0);
		glVertex3f(10, 0, 0);
		glVertex3f(-10, 0, 0);
		glColor3f(0, 1, 1);
		glVertex3f(15, 0, 0);
		glVertex3f(10, 0, 0);
		//ligne z, bleu
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 10);
		glVertex3f(0, 0, -10);
		glColor3f(0, 1, 1);
		glVertex3f(0, 0, 15);
		glVertex3f(0, 0, 10);
	glEnd();
}