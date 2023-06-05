#include "../include/menu.h"

Menu::Menu() 
{
  m_menu = true;
  m_type = 0;
  m_level = 1;
}

/* ********** G E T T E R S ********** */
bool Menu::getMenu() {
  return m_menu;
}

int Menu::getType() {
  return m_type;
}

int Menu::getLevel() {
  return m_level;
}

/* ********** S E T T E R S ********** */
void Menu::setMenu(bool menu) {
  m_menu = menu; 
}

void Menu::setType(int type) {
  m_type = type; 
}

void Menu::setLevel(int level) {
  m_level = level; 
}