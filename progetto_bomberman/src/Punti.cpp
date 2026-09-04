#include "Punti.hpp"
punti::punti() {
    getmaxyx(stdscr, maxy, maxx);
    win1 = NULL;
    larghezza = 10;
    altezza = 3;
    punteggio=0;
};

//Restituisce punteggio
int punti:: puntif() {
    return punteggio;
}

//Azzera il punteggio
void punti::azzera() {
    punteggio=0;
};

//Disegna la finestra dei punti a seconda della grandezza dello schermo
void punti::finestra() {
    getmaxyx(stdscr, maxy, maxx);
    int y = 2;
    int x = maxx - larghezza - 5;
    if (x < 0) x = 0;
    if (win1 == NULL) {
        win1 = newwin(altezza, larghezza, y, x);
    }else {
        wresize(win1, altezza, larghezza);
        mvwin(win1, y, x);
    }
    box(win1, 0, 0);
    scrivipunti();
};

//Scrive i punti aggiornati nella finestra
void punti::scrivipunti() {
    if (win1 == NULL) return;
    mvwprintw(win1, 1, 2, "%06d", punteggio);
    wrefresh(win1);
};

//Modifica il punteggio attuale
void punti::modificapunti(int tasto) {
    switch (tasto) {
        case 'q':
            punteggio+=50;
            break;
        case 'w':
            punteggio+=100;
            break;
        case 'y':
            punteggio+=150;
            break;
        case 'x':
            azzera();
            break;
    }
    scrivipunti();
};void punti::addpunti(int p) { punteggio += p; }
