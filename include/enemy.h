#ifndef ENEMY_H
#define ENEMY_H
#include <stdio.h>

class Enemy
{
    public:
    
        Enemy(int w, int h, int km, int points, bool left);

        /* ********** F U N C T I O N S ********** */
        
        /* ********** G E T T E R S ********** */
        int getW();
        int getH();
        float getD();
        bool getLeft();

        /* ********** S E T T E R S ********** */
        void setD(float d);
        void setDWithWalk(float walk);

    private:
        int m_w;
        int m_h;
        float m_d;
        int m_km;
        int m_points;
        bool m_left;
};
#endif