#pragma once

#include "Librerie.hpp"
#include"Schermo.hpp"
struct cl{
    char nom[100];
    int punt;
};

class Classifica {
protected:
    int contaRighe(char t[]);
    char numpunti[60];
    Schermo sch;
    cl classifica[200];
    int punti;
    WINDOW* backBtn;
    void aggiornaBackButton();
    bool isClickBackButton(MEVENT& event);
public:
    Classifica();
    void Npunti();
    void mostra(int PUN);
    void addclass(char t[],char nome[],int pu);
};
