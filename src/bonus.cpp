#include "../include/bonus.h"

Bonus::Bonus(int type, int x, int z, int h, int depth) 
{
  m_type = type;
  m_x = x;
  m_z = z;
  m_h = h;
  m_d = depth;
}

/* ********** G E T T E R S ********** */
int Bonus::getType() { 
  return m_type;}

int Bonus::getX() { 
  return m_x;}

int Bonus::getZ() { 
  return m_z;}

int Bonus::getH() {
  return m_h;}

int Bonus::getD() {
  return m_d;}

/* ********** S E T T E R S ********** */
void Bonus::setDWithWalk(float walk) {
    m_d -= walk;
}