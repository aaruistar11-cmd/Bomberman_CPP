#ifndef BOMBERMAN_PUNTI_H
#define BOMBERMAN_PUNTI_H
using namespace std;
#include <iostream>
#include <ncurses.h>
class punti {
protected:
    WINDOW* win1;
    int larghezza;
    int altezza;
    int maxx,maxy;
    int punteggio;
public:
    punti();
    int puntif();
    void azzera();
    void finestra();
    void scrivipunti();
    void modificapunti(int tasto);
    void addpunti(int p);
};
#endif
