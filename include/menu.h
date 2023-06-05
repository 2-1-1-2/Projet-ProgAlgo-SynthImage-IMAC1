#ifndef MENU_H
#define MENU_H

class Menu 
{
  public:
    Menu();
    /*Menu(const Menu& other);
    Menu& operator=(const Menu& other);*/

    /* ********** G E T T E R S ********** */
    bool getMenu();
    int getType();

    /* ********** S E T T E R S ********** */
    void setMenu(bool menu);
    void setType(int type);
  private:
    bool m_menu;
    bool m_type;
};

#endif
