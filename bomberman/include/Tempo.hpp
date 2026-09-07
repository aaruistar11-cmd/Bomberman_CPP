#pragma once

#include "Librerie.hpp"
class tempo {
protected:
    int durata;
    time_t tempo_inizio;
public:
    int tempo_rimasto;
    tempo();
    void addpausa(int t);
    void diminuiscitempo();
    void avvia(int t);
    void aggiungiTempo(int t);
};