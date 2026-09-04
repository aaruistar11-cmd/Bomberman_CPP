#ifndef BOMBERMAN_TEMPO_H
#define BOMBERMAN_TEMPO_H
using namespace std;
#include <ncurses.h>
#include <ctime>
class tempo {
protected:
    WINDOW* win1;
    int durata;
    time_t tempo_inizio;
    int larghezza;
    int altezza;
    int maxx, maxy;
public:
    int tempo_rimasto;
    tempo();
    void addpausa(int t);
    void finestra();
    void scrivitempo();
    void diminuiscitempo();
    void avvia(int t);
    void aggiungiTempo(int t);
};
#endif