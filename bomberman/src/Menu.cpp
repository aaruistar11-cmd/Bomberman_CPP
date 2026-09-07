#include "Librerie.hpp"
#include "Menu.hpp"

Menu::Menu() {
    win = NULL;
    win2 = NULL;
    for (int i = 0; i < 3; i++)
        but[i] = NULL;
    strcpy(Titolo, "####      ##     #     #  ####   ####  ####   #     #    #    #     #\n#   #   #    #   ##   ##  #   #  #     #   #  ##   ##   # #   ##    #\n#   #  #      #  # # # #  #   #  #     #   #  # # # #  #   #  # #   #\n####   #      #  #  #  #  ####   ####  ####   #  #  #  #####  #  #  #\n#   #  #      #  #     #  #   #  #     #  #   #     #  #   #  #   # #\n#   #   #    #   #     #  #   #  #     #   #  #     #  #   #  #    ##\n####      ##     #     #  ####   ####  #   #  #     #  #   #  #     #\n");
    strcpy(Titolo2,"BOMBERMAN");
}

// Stampa tutto a schermo
void Menu::drawMenu() {
    werase(stdscr);
    touchwin(stdscr);
    refresh();
    drawtitle();
    drawbutton("Start", 0);
    drawbutton("Classifica", 1);
    drawbutton("Exit", 2);
    refresh();
}

// Disegna la scritta Bomberman (grande o piccola)
void Menu::drawtitle() {
    if (win != NULL) {
        delwin(win);
        win = NULL;
    }
    getmaxyx(stdscr, startY, startX);
    if (startY > 30 && startX > 80) {
        width = 77;
        height = 11;
        win = newwin(height, width, 3, (startX - width) / 2 + 5);
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 2, 0, "%s", Titolo);
        wattroff(win, COLOR_PAIR(1));
        wrefresh(win);
    } else {
        win = newwin(3, 15, 2, (startX - 12) / 2 - 2);
        wattron(win, A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);
        mvwprintw(win, 1, 3, Titolo2);
        box(win, 0, 0);
        wattroff(win, A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);
        wrefresh(win);
    }
}

// Crea le caselle dei bottoni
void Menu::drawbutton(char t[], int el) {
    int maxY, maxX;
    int x, y, h, w;
    getmaxyx(stdscr, maxY, maxX);
    if (but[el] != NULL) {
        delwin(but[el]);
        but[el] = NULL;
    }
    if (el == 0) {
        getbegyx(win, y, x);
        getmaxyx(win, h, w);
    } else {
        getbegyx(but[el - 1], y, x);
        getmaxyx(but[el - 1], h, w);
    }
    win2 = newwin(3, strlen(t) + 4, h + y + 1, (maxX - strlen(t))/ 2 - 2);
    box(win2, 0, 0);
    mvwprintw(win2, 1, 2, "%s", t);
    wrefresh(win2);
    but[el] = win2;
}

// Ritorna 0, 1, o 2 in base a cosa si clicca
int Menu::controllaClick(MEVENT& event) {
    for (int i = 0; i < 3; i++) {
        if (but[i] == NULL) continue;
        int by, bx, bh, bw;
        getbegyx(but[i], by, bx);
        getmaxyx(but[i], bh, bw);
        if (event.y >= by && event.y < by + bh &&
            event.x >= bx && event.x < bx + bw) {
            return i;
            }
    }
    return -1;
}