#ifndef CORRIDOR_H
#define CORRIDOR_H
#include <vector>
#include "enemy.h"
#include "dataEnemy.h"
#include "struct.h"
#include "bonus.h"

class Corridor
{
    public:
    
        Corridor(int x, int y, int z, float speed);
        Corridor(){};

        /* ********** F U N C T I O N S ********** */
        void drawCorridor(std::vector<ImgTexture>& v_texture);
        void drawBonus(std::vector<Bonus>& v_bonus, std::vector<ImgTexture>& v_texture);
        void drawEnemys(std::vector<Enemy>& v_enemys, std::vector<ImgTexture>& v_texture);
        void drawLines(std::vector<Enemy> &v_enemys, std::vector<Bonus> &v_bonus, std::vector<ImgTexture>& v_texture);
        void loadEnemys(std::vector<Enemy> &v_enemys);
        void loadBonus(std::vector<Bonus> &v_bonus);

        /* ********** G E T T E R S ********** */
        int getZ();
        int getKm();
        int getWalk();
        int getSpeed();
        float getPos(char pos);

        /* ********** S E T T E R S ********** */
        void setWalk();
        void setWalk(int walk);

    private:
        int m_x;
        int m_y;
        int m_z;
        int m_start;
        float m_km;
        float m_walk;
        float m_speed;
        float m_colors[6];
        float m_lines[7];
};
#endif