#include <GL/gl.h>
#include <GL/glu.h>
#include "math.h"
#include "algorithm"
#include "3D_tools.h"
#include "racket.h"

Racket::Racket(float x, float y, float z)
{
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    this->m_length = 2.5;
    this->m_pos = 0;
    this->m_speed = 0.3;
}

void Racket::drawRacket()
{

    glColor3f(1, 0, 1);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex3f(m_x + m_length, m_y, m_z + m_length);
    glVertex3f(m_x - m_length, m_y, m_z + m_length);
    glVertex3f(m_x - m_length, m_y, m_z - m_length);
    glVertex3f(m_x + m_length, m_y, m_z - m_length);
    glEnd();
}

/* ********** G E T T E R S ********** */
int Racket::getPos()
{
    return this->m_pos;
}

/* ********** S E T T E R S ********** */
void Racket::setPos()
{
    this->m_pos += m_speed;
}

void Racket::setPos(float posX, float posY)
{
    this->m_x = posX;
    this->m_z = posY;
}