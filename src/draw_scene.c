#include "draw_scene.h"
#include "3D_tools.h"
#include "math.h"

void drawBase() 
{
	glPushMatrix();
		glColor3f(235.0/255.0, 207.0/255.0, 52.0/255.0);
		glScalef(3.0,3.0,0.1);
		drawCircle();
	glPopMatrix();

	glPushMatrix();
		glScalef(2.0,2.0,10.0);
		drawCone();
	glPopMatrix();
}

void drawArm() 
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
}

void drawCorridor() 
{
	// Carré du bas
		int x = 25;
		int y = 60;
		int z = 12;
		
		// carré du bas
		glColor3f(0.5, 0.5, 1);
		// deux premiers points = ceux du bas
		glBegin(GL_QUADS);
			glVertex3f(-x, -14, -z);
			glVertex3f(x, -14, -z);
			glVertex3f(x, y, -z);
			glVertex3f(-x, y, -z);
		glEnd();

		// carré du haut
		glColor3f(0.5, 0.5, 1);
		// carré du bas
		glBegin(GL_QUADS);
			glVertex3f(-x, y, z);
			glVertex3f(x, y, z);
			glVertex3f(x, -y, z);
			glVertex3f(-x, -y, z);
		glEnd();

		// carré de gauche
		glColor3f(0.5, 0.8, 1);
		// carré du bas
		glBegin(GL_QUADS);
			glVertex3f(-x, -14, -z);
			glVertex3f(-x, y, -z);
			glVertex3f(-x, y, z);
			glVertex3f(-x, -y, z);
		glEnd();

		// carré de droite
		glColor3f(0.5, 0.8, 1);
		// carré du bas
		glBegin(GL_QUADS);
			glVertex3f(x, -14, -z);
			glVertex3f(x, y, -z);
			glVertex3f(x, y, z);
			glVertex3f(x, -y, z);
		glEnd();
}

void drawLines() 
{
	// Carré du bas
		int x = 25;
		int y = 60;
		int z = 12;
		
			glColor3f(1, 1, 1);
			glLineWidth(2);
			// deux premiers points = ceux du bas
			for(size_t i = 0; i < 7; i++)
			{
				glBegin(GL_LINE_LOOP);
					glVertex3f(-x+0.1, y, -z+0.1);
					glVertex3f(x-0.1, y, -z+0.1);
					glVertex3f(x-0.1, y, z);
					glVertex3f(-x+0.1, y, z);
				glEnd();
				y-=10;
			}
}

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