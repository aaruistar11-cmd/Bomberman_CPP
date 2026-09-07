#pragma once

#include "Librerie.hpp"
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