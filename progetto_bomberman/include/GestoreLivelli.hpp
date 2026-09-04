#ifndef GESTORELIVELLI_HPP
#define GESTORELIVELLI_HPP

#include "Mappa.hpp"

// ============================================================================
// CLASSE GESTORE LIVELLI (LISTA BIDIREZIONALE)
// ============================================================================
// Soddisfa esplicitamente il requisito: "I Livelli sono implementati tramite 
// liste bidirezionali che permettono di passare da un livello all'altro".
// ============================================================================
class GestoreLivelli {
protected:
    Mappa* primoLivello;
    Mappa* livelloAttuale;

public:
    GestoreLivelli();
    
    // Inserisce in coda alla lista bidirezionale
    void aggiungiLivello(Mappa* nuovoLivello);
    
    // Spostamento nella lista (tasti n e p)
    void prossimoLivello();
    void livelloPrecedente();
    
    // Rimuove e dealloca un livello, restituendo un livello adiacente
    Mappa* rimuoviLivello(Mappa* mappaDaRimuovere);
    
    // Restituisce il puntatore per il rendering nel main
    Mappa* getLivelloCorrente();
    
    // Utilità per liberare la memoria (delete manuale come da regole)
    Mappa* getPrimoLivello();
};

#endif
