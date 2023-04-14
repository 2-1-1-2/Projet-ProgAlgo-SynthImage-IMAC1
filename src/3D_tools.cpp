#include "3D_tools.h"

/* Camera parameters and functions */
/*float theta = 90.0f; // Angle between x axis and viewpoint
float phy = 90.0f; // Angle between z axis and viewpoint
float dist_zoom = 30.0f; // Distance between origin and viewpoint*/

void setCamera() 
{
	/*gluLookAt(dist_zoom*cos(toRad(theta))*sin(toRad(phy)),
			  dist_zoom*sin(toRad(theta))*sin(toRad(phy)),
			  dist_zoom*cos(toRad(phy)),
			  0.0,0.0,0,
			  0.0,0.0,1.0);*/
	gluLookAt(0, -30, 0,
			  0, 0, 0,
			  0, 0, 1);
}

/* Convert degree to radians */
float toRad(float deg) 
{
	return deg*M_PI/180.0f;
}


void drawSquare(int x, int y, int z, int start, bool vertical) 
{
	if(vertical)
	{
		glBegin(GL_QUADS);
			glVertex3f(-x, start, z);
			glVertex3f(x, start, z);
			glVertex3f(x, y, z);
			glVertex3f(-x, y, z);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
			glVertex3f(x, start, z);
			glVertex3f(x, y, z);
			glVertex3f(x, y, -z);
			glVertex3f(x, start, -z);
		glEnd();
	}
}

void drawSquare(int x1, int x2, int y, int z) 
{
	glBegin(GL_QUADS);
		glVertex3f(x1, y, -z);
	    glVertex3f(x2, y, -z);
	    glVertex3f(x2, y, z);
	    glVertex3f(x1, y, z);
	glEnd();
}

void drawLineLoop(int x, int y, int z) 
{
	glBegin(GL_LINE_LOOP);
        glVertex3f(-x+0.1, y, -z+0.1);
        glVertex3f(x-0.1, y, -z+0.1);
        glVertex3f(x-0.1, y, z);
        glVertex3f(-x+0.1, y, z);
    glEnd();
}

void drawCircle() 
{
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,0.0);
		float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawCone() 
{
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,1.0);
		float step_rad = 2*M_PI/(float)NB_SEG_CIRCLE;
		for(int i=0;i<=NB_SEG_CIRCLE;i++) {
			glVertex3f(cos(i*step_rad),sin(i*step_rad),0.0f);
		}
	glEnd();
}

void drawSphere() 
{
	gluSphere(gluNewQuadric(),1.0,NB_SEG_CIRCLE,NB_SEG_CIRCLE);
}
