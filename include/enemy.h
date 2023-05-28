#ifndef ENEMY_H
#define ENEMY_H
#include <stdio.h>

class Enemy
{
    public:
    
        Enemy();
        Enemy(int w, int h, int d, int points, int left, int up);
        Enemy (const Enemy &e);

        /* ********** F U N C T I O N S ********** */
        
        /* ********** G E T T E R S ********** */
        int getW();
        int getH();
        float getD();
        int getLeft();
        int getUp();
        int getRot();

        /* ********** S E T T E R S ********** */
        void setD(float d);
        void setDWithWalk(float walk);
        void setRot(int rot);

    private:
        int m_w;
        int m_h;
        float m_d;
        int m_points;
        int m_left;
        int m_up;
        int m_rot;
};
#endif