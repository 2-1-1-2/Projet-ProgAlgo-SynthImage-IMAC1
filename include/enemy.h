#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
    public:
    
        Enemy(int w, int h, int points, bool left);

        /* ********** F U N C T I O N S ********** */

        /* ********** G E T T E R S ********** */

        /* ********** S E T T E R S ********** */

    private:
        int m_w;
        float m_h;
        int m_points;
        bool left;
};
#endif