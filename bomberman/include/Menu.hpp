#pragma once

#include "Librerie.hpp"
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
    int controllaClick(MEVENT& event);
};