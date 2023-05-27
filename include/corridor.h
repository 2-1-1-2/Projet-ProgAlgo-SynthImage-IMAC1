#ifndef CORRIDOR_H
#define CORRIDOR_H
#include <vector>
#include "enemy.h"
#include "dataEnemy.h"

class Corridor
{
    public:
    
        Corridor(int x, int y, int z, float speed);

        /* ********** F U N C T I O N S ********** */
        void drawCorridor();
        void drawLines(std::vector<Enemy> &v_enemys);
        void loadEnemys(std::vector<Enemy> &v_enemys);

        /* ********** G E T T E R S ********** */
        int getZ();
        int getWalk();

        /* ********** S E T T E R S ********** */
        void setWalk();
        void setWalk(int walk);

    private:
        int m_x;
        float m_y;
        int m_z;
        int m_start;
        float m_km;
        float m_walk;
        float m_speed;
        float m_colors[6];
        float m_lines[7];
};
#endif