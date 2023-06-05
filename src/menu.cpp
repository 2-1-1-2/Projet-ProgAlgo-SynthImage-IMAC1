#include "../include/menu.h"

Menu::Menu() 
{
  m_menu = true;
  m_type = 0;
}

/* ***** Constructeur de copie ***** */
/*Menu::Menu(const Menu& other)
{
  m_menu = other.m_menu;
  m_type = other.m_type;
}

Menu& Menu::operator=(const Menu& other)
{
  if (this != &other) // Vérifier si les objets sont différents pour éviter une auto-assignation
  {
    m_menu = other.m_menu;
    m_type = other.m_type;
  }
  return *this;
}*/
/* ********** G E T T E R S ********** */
bool Menu::getMenu() {
  return m_menu;
}

int Menu::getType() {
  return m_type;
}

/* ********** S E T T E R S ********** */
void Menu::setMenu(bool menu) {
  m_menu = menu; 
}

void Menu::setType(int type) {
  m_type = type; 
}