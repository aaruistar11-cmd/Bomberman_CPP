#ifndef BOMBERMAN_FINE_H
#define BOMBERMAN_FINE_H
using namespace std;
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <cstring>
#include "Schermo.hpp"
#include "Classifica.hpp"

class fine {
protected:
    WINDOW*win3;
    WINDOW*win4;
    char nome[100];
    char end[100];
    char end2[100];
    Schermo sch;
    Classifica cl;
public:
    fine();
    void drawnome(int pu);
    bool drawend();
};
#endif