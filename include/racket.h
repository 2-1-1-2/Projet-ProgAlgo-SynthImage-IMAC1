#ifndef RACKET_H
#define RACKET_H

class Racket
{
public:
    Racket(float x, float y, float z);

    /* ********** F U N C T I O N S ********** */
    void drawRacket();

    /* ********** G E T T E R S ********** */
    int getPos();

    /* ********** S E T T E R S ********** */
    void setPos();
    void setPos(float posX, float posY);

private:
    float m_x;
    float m_y;
    float m_z;
    int m_length;
    float m_pos;
    float m_speed;
};
#endif