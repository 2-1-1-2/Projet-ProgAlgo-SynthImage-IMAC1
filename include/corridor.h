#ifndef CORRIDOR_H
#define CORRIDOR_H

class Corridor
{
    public:
    
        Corridor(int x, int y, int z, float speed);

        /* ********** F U N C T I O N S ********** */
        void drawCorridor();
        void drawLines();

        /* ********** G E T T E R S ********** */
        int getWalk();

        /* ********** S E T T E R S ********** */
        void setWalk();
        void setWalk(int walk);

    private:
        int m_x;
        float m_y;
        int m_z;
        int m_start;
        float m_walk;
        float m_speed;
        float m_colors[6];
        float m_lines[7];
};
#endif