#include <GL/gl.h>
#include <GL/glu.h>
#include "math.h"
#include "algorithm"
#include "3D_tools.h"
#include "corridor.h"

Corridor::Corridor(int x, int y, int z, float speed)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_start = -14;
    m_walk = 0;
    m_speed = 0.3;

    float colors[6] = {0.5, 0.5, 1, 0.5, 0.8, 1};
    std::copy(colors, colors + 6, m_colors);

    int temp = y;
    for (size_t i = 0; i < 7; i++)
    {
        m_lines[i] = temp;
        temp -= 10;
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

// to make go backward the inside of the corridor
void Corridor::drawLines()
{
    // color blue
    glColor3f(1, 1, 1);
    // size of the line
    glLineWidth(2);
    // To create the 7 lines
    for (size_t i = 0; i < 7; i++)
    {
        m_lines[i] -= m_walk;

        if (m_lines[i] <= -10)
            m_lines[i] = m_y - 1;

        drawLineLoop(m_x, m_lines[i], m_z);
    }
    m_walk = 0;
}

/* ********** G E T T E R S ********** */
int Corridor::getWalk()
{
    return m_walk;
}


int Corridor::getSpeed()
{
    return m_speed;
}
float Corridor::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}

/* ********** S E T T E R S ********** */
void Corridor::setWalk()
{
    m_walk += m_speed;
}

void Corridor::setWalk(int walk)
{
    m_walk = walk;
}