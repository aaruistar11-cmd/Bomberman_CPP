#pragma once

#include "Librerie.hpp"
// Classe per gestire logica e grafica della mappa
class Mappa {
protected:
    // Matrice 20x40 del labirinto
    char griglia[20][40];
    
    // Variabili per mantenere le dimensioni effettive in uso durante i cicli.
    int altezza;
    int larghezza;

    // Serve per la funzione del random custom
    unsigned long int seme_casuale;

public:
    // Puntatori per la lista (Livelli)
    Mappa* next;
    Mappa* prev;
    
    // Identificativo del livello
    int idLivello;
    int nemici_rimasti;

    // Inizializza id e roba base
    Mappa(int livello, unsigned int semeBase);

    // Riempie la matrice in modo procedurale
    void inizializzaGriglia();

    // Metodi per il sistema di Collisioni e Movimento
    char getCella(int y, int x);
    void setCella(int y, int x, char valore);

    // Stampa la cornice della mappa e le info ai lati
    void disegnaLayout(int punti, int tempoRimanente, int vite);

    // Colora e disegna bomberman o nemici
    void stampaEntita(int y, int x, char c, int color_pair);

    // Calcolo del random senza librerie proibite
    int generaCasuale();
};
