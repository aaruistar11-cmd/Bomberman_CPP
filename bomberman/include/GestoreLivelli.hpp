#pragma once

#include "Librerie.hpp"
#include "Mappa.hpp"

// Classe per la lista dei livelli
class GestoreLivelli {
protected:
    Mappa* primoLivello;
    Mappa* livelloAttuale;

public:
    GestoreLivelli();
    
    // Aggiunge mappa in fondo
    void aggiungiLivello(Mappa* nuovoLivello);
    
    // Cancella un livello dalla memoria
    Mappa* rimuoviLivello(Mappa* mappaDaRimuovere);
    
    // Ritorna il puntatore iniziale
    Mappa* getPrimoLivello();
};
