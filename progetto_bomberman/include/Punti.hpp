#ifndef BOMBERMAN_PUNTI_H
#define BOMBERMAN_PUNTI_H
using namespace std;
#include <iostream>
#include <ncurses.h>
class punti {
protected:
    int punteggio;
public:
    punti();
    int puntif();
    void azzera();
    void addpunti(int p);
};
#endif
