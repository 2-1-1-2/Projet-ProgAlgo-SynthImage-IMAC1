#include <GL/gl.h>
#include <GL/glu.h>
#include "math.h"
#include "algorithm"
#include "3D_tools.h"
#include "corridor.h"

Corridor::Corridor(int x, int y, int z, float speed)
{
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    this->m_start = -14;
    this->m_walk = 0;
    this->m_speed = 0.3;

    float colors[6] = {0.5, 0.5, 1, 0.5, 0.8, 1};
    std::copy(colors, colors+6, this->m_colors);

    int temp = y;
    for(size_t i = 0; i < 7; i++)
    {
        this->m_lines[i] = temp;
        temp-=10;
    }
}

void Corridor::drawCorridor()
{       
        // bottom square
        glColor3f(m_colors[0], m_colors[1], m_colors[2]);
        drawSquare(m_x, m_y, -m_z, m_start, true);

        // top square
        drawSquare(m_x, m_y, m_z, m_start, true);

        // left square
        glColor3f(m_colors[3], m_colors[4], m_colors[5]);
        drawSquare(-m_x, m_y, m_z, m_start, false);

        // right square
        drawSquare(m_x, m_y, m_z, m_start, false);
}

void Corridor::drawLines()
{       

        /*// to make walk the inside of the corridor
        y-=walk;*/
        glColor3f(1, 1, 1);
        glLineWidth(2);
        // deux premiers points = ceux du bas
        for(size_t i = 0; i < 7; i++)
        {
            m_lines[i] -= m_walk;
            if(m_lines[i] <= -10)
                m_lines[i] = m_y-1;

            glBegin(GL_LINE_LOOP);
                glVertex3f(-m_x+0.1, m_lines[i], -m_z+0.1);
                glVertex3f(m_x-0.1, m_lines[i], -m_z+0.1);
                glVertex3f(m_x-0.1, m_lines[i], m_z);
                glVertex3f(-m_x+0.1, m_lines[i], m_z);
            glEnd();
        }
        m_walk = 0;
}

/* ********** G E T T E R S ********** */
int Corridor::getWalk()
{
    return this->m_walk;
}

/* ********** S E T T E R S ********** */
void Corridor::setWalk()
{
    this->m_walk += m_speed;
}

void Corridor::setWalk(int walk)
{
    this->m_walk = walk;
}