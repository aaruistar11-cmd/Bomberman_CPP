#ifndef BOMBERMAN_MENU_H
#define BOMBERMAN_MENU_H
#ifndef BOMBERMAN_MENU_HPP
#define BOMBERMAN_MENU_HPP
using namespace std;
#include<cmath>
#include <ncurses.h>
#include <cstring>

class Menu {
protected:
    char Titolo[500];
    char Titolo2[500];
    WINDOW* win;
    WINDOW* win2;
    WINDOW* but[3];
    int width, height;
    int startX, startY;
    char nome[100];
public:
    Menu();
    void drawMenu();
    void drawtitle();
    void drawbutton(char t[], int el);
    void azionebut(int i, MEVENT& event);
    int controllaClick(MEVENT& event);
};

#endif
#endif