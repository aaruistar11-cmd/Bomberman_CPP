#ifndef MAPPA_HPP
#define MAPPA_HPP

#include <ncurses.h>

// ============================================================================
// CLASSE MAPPA
// ============================================================================
// Questa classe gestisce la matrice logica del gioco Bomberman e si occupa
// interamente del rendering visivo dell'interfaccia utente (UI) tramite
// le primitive di ncurses.
// 
// REGOLE RISPETTATE:
// - Niente parola chiave 'private' (uso 'protected').
// - Nessun distruttore (gestione memoria lasciata manuale in caso di allocazioni).
// - Niente std::string, solo array nativi di char.
// - Niente vector, costrutti moderni o template.
// - Niente puntatore 'this' nell'implementazione.
// ============================================================================
class Mappa {
protected:
    // Matrice logica del gioco. Le dimensioni richieste sono minimo 40x20.
    // Usiamo esattamente 20 righe e 40 colonne come richiesto dalla specifica.
    char griglia[20][40];
    
    // Variabili per mantenere le dimensioni effettive in uso durante i cicli.
    int altezza;
    int larghezza;

    // Variabile per mantenere lo stato del generatore pseudo-casuale interno.
    // Rispettando il divieto di usare librerie extra come <cstdlib>.
    unsigned long int seme_casuale;

public:
    // Puntatori per la lista bidirezionale (pubblici per accesso dal Gestore)
    Mappa* next;
    Mappa* prev;
    
    // Identificativo del livello
    int idLivello;
    int nemici_rimasti;

    // Costruttore base: inizializza le dimensioni e il seme senza usare 'this'.
    Mappa(int livello, unsigned int semeBase);

    // Funzione corposa e complessa (>40 righe) per generare proceduralmente
    // i muri solidi, i muri distruttibili, la safe-zone del giocatore
    // e il piazzamento dei nemici. Popola l'array "griglia".
    void inizializzaGriglia();

    // Metodi per il sistema di Collisioni e Movimento
    char getCella(int y, int x);
    void setCella(int y, int x, char valore);

    // Funzione corposa e complessa (>40 righe) che effettua il rendering 
    // a schermo. Disegna la cornice, calcola il layout, inietta
    // dinamicamente punteggio e tempo (senza sprintf), e applica i 
    // colori corretti a ogni singolo blocco (muri solidi vs distruttibili).
    void disegnaLayout(int punti, int tempoRimanente, int vite);

    // Disegna entità dinamiche sopra la mappa statica
    void stampaEntita(int y, int x, char c, int color_pair);

    // Algoritmo LCG (Linear Congruential Generator) interno.
    // Genera numeri casuali necessari per il piazzamento procedurale
    // permettendoci di non violare il vincolo "solo ncurses e ctime".
    int generaCasuale();
};

#endif
