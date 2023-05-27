#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/math.h"
#include <algorithm>
#include "../include/3D_tools.h"
#include "../include/corridor.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "algorithm"
#include "enemy.h"

Corridor::Corridor(int x, int y, int z, float speed)
{
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    this->m_start = -14;
    this->m_walk = 0;
    this->m_km = -14;
    this->m_speed = speed;

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
void Corridor::drawLines(std::vector<Enemy> &v_enemys)
{       
    // color white
    glColor3f(1, 1, 1);
    // size of the line
    glLineWidth(2);
    // To create the 7 lines
    for(size_t i = 0; i < 7; i++)
    {
        m_lines[i] -= m_walk;

        if (m_lines[i] <= -10)
            m_lines[i] = m_y - 1;

        drawLineLoop(m_x, m_lines[i], m_z);
    }
    // To create the enemys
    for(Enemy &element : v_enemys)
    {
        // to make walk the enemys
        element.setDWithWalk(m_walk);
        // color of the enemy
        glColor3f(1, 0, 0);

        if(element.getLeft() != -1 && element.getUp() != -1)
        {
            // Gauche
            if(element.getLeft())
            {
                // Haut
                if(element.getUp())
                    drawEnemy(-m_x, -m_x + element.getW(), element.getD(), m_z - element.getH(), m_z);
                // Bas
                else
                    drawEnemy(-m_x, -m_x + element.getW(), element.getD(), -m_z, -m_z + element.getH());
            }
            // Droite
            else
            {
                // Haut
                if(element.getUp())
                    drawEnemy(m_x - element.getW(), m_x, element.getD(), m_z - element.getH(), m_z);
                // Bas    
                else
                    drawEnemy(m_x - element.getW(), m_x, element.getD(), -m_z, -m_z + element.getH());
            }
        }
        /* *** Enemy is completely horizontal *** */
        else if(element.getLeft() == -1)
        {
            // il est en haut
            if(element.getUp())
                drawHorizontalEnemy(m_x, element.getD(), m_z - element.getH(), m_z);
            // il est en bas
            else
                drawHorizontalEnemy(m_x, element.getD(), -m_z, -m_z + element.getH());
        }
        /* *** Enemy is completely vertical *** */
        else
        {
            if(element.getLeft())
                drawVerticalEnemy(-m_x, -m_x + element.getW(), element.getD(), m_z);
            else
                drawVerticalEnemy(m_x, m_x - element.getW(), element.getD(), m_z);
        }
    }
    m_walk = 0;
}

// to initialize the enemys
void Corridor::loadEnemys(std::vector<Enemy> &v_enemys)
{
    std::map<std::string, std::tuple<int, int, int, int, int, int>> enemyMap;
    std::string line;
    std::ifstream file("src/enemys.txt");
    std::string e;
    int d;

    if (!file.is_open())
        perror("error while opening file\n");

    initializeEnemyMap(enemyMap);
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        
        if (!(iss >> e >> d)) 
            perror("not the good number of elements");

        Enemy enemy = createEnemy(enemyMap, e, d);
        v_enemys.push_back(enemy);
    }

    if (file.bad())
        perror("error while reading file");

    file.close();
}

/* ********** G E T T E R S ********** */
int Corridor::getZ() {
    return this->m_z;
}

int Corridor::getWalk() {
    return m_walk;
}


int Corridor::getSpeed() {
    return m_speed;
}

float Corridor::getPos(char pos) {
  return pos == 'X' ? m_x : pos == 'Y' ? m_y : m_z;
}

/* ********** S E T T E R S ********** */
void Corridor::setWalk()
{
    this->m_walk += m_speed;
    this->m_km += m_speed;
    printf("Km: %f\n", m_km);
}

void Corridor::setWalk(int walk) {
    m_walk = walk;
}