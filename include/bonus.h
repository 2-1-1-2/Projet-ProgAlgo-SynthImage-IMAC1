#ifndef BONUS_H
#define BONUS_H

class Bonus
{
    public:
    
        Bonus(int type, int x, int z, int h, float depth);

        /* ********** F U N C T I O N S ********** */

        /* ********** G E T T E R S ********** */
        int getType();
        int getX();
        int getZ();
        int getH();
        float getD();

        /* ********** S E T T E R S ********** */
        void setDWithWalk(float walk);

    private:
        int m_type;
        int m_x;
        int m_z;
        int m_h;
        float m_d;
};
#endif