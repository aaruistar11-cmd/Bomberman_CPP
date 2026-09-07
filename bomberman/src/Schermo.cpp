#include "Librerie.hpp"
#include "Schermo.hpp"

//Mi crea una finestra di avvertimento se lo schermo è troppo piccolo
bool Schermo::controllaDimensione(int MIN_X, int MIN_Y) {
    int curY, curX;
    getmaxyx(stdscr, curY, curX);
    if (curY >= MIN_Y && curX >= MIN_X) {
        return false;
    }
    werase(stdscr);
    box(stdscr, 0, 0);
    if (curX>42) {
        mvwprintw(stdscr, 2, 2, "ATTENZIONE: Finestra troppo piccola!");
        mvwprintw(stdscr, 3, 2, "Allarga il terminale per continuare...");
    }else {
        mvwprintw(stdscr,1,1,"Finestra troppo piccola");
    }
    refresh();
    wtimeout(stdscr, 100);
    while (curY < MIN_Y || curX < MIN_X) {
        int ch = getch();
        if (ch == KEY_RESIZE) {
            resize_term(0, 0);
        }
        int newY, newX;
        getmaxyx(stdscr, newY, newX);
        if (newY != curY || newX != curX || ch == KEY_RESIZE) {
            curY = newY;
            curX = newX;
            if (curY >= MIN_Y && curX >= MIN_X) break;
            clear();
            box(stdscr, 0, 0);
            if (curX>42) {
                mvwprintw(stdscr, 2, 2, "ATTENZIONE: Finestra troppo piccola!");
                mvwprintw(stdscr, 3, 2, "Allarga il terminale per continuare...");
            }else {
                mvwprintw(stdscr,1,1,"Finestra troppo piccola");
            }
            refresh();
        }
    }
    wtimeout(stdscr, -1);
    werase(stdscr);
    refresh();
    return true;
}