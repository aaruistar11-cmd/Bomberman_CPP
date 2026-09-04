#include "GestoreLivelli.hpp"

// Usiamo 0 al posto di NULL se non è definito per evitare macro strane
#ifndef NULL
#define NULL 0
#endif

// ============================================================================
// COSTRUTTORE
// ============================================================================
GestoreLivelli::GestoreLivelli() {
    primoLivello = NULL;
    livelloAttuale = NULL;
}

// ============================================================================
// AGGIUNGI LIVELLO ALLA LISTA BIDIREZIONALE
// ============================================================================
void GestoreLivelli::aggiungiLivello(Mappa* nuovoLivello) {
    if (primoLivello == NULL) {
        // Se la lista è vuota, il nuovo è sia il primo che l'attuale
        primoLivello = nuovoLivello;
        livelloAttuale = nuovoLivello;
        nuovoLivello->prev = NULL;
        nuovoLivello->next = NULL;
    } else {
        // Scorriamo fino in fondo per appendere il nuovo livello
        Mappa* temp = primoLivello;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        
        // Colleghiamo in modo bidirezionale
        temp->next = nuovoLivello;
        nuovoLivello->prev = temp;
        nuovoLivello->next = NULL;
    }
}

// ============================================================================
// SPOSTAMENTO AVANTI (Tasto 'n')
// ============================================================================
void GestoreLivelli::prossimoLivello() {
    if (livelloAttuale != NULL && livelloAttuale->next != NULL) {
        livelloAttuale = livelloAttuale->next;
    }
}

// ============================================================================
// SPOSTAMENTO INDIETRO (Tasto 'p')
// ============================================================================
void GestoreLivelli::livelloPrecedente() {
    if (livelloAttuale != NULL && livelloAttuale->prev != NULL) {
        livelloAttuale = livelloAttuale->prev;
    }
}

// ============================================================================
// GETTER
// ============================================================================
Mappa* GestoreLivelli::getLivelloCorrente() {
    return livelloAttuale;
}

Mappa* GestoreLivelli::getPrimoLivello() {
    return primoLivello;
}

// ============================================================================
// RIMUOVI LIVELLO
// ============================================================================
Mappa* GestoreLivelli::rimuoviLivello(Mappa* m) {
    if (m == NULL) return NULL;
    
    Mappa* adiacente = NULL;
    if (m->next != NULL) adiacente = m->next;
    else if (m->prev != NULL) adiacente = m->prev;
    
    // Aggiorna i puntatori dei nodi adiacenti
    if (m->prev != NULL) m->prev->next = m->next;
    if (m->next != NULL) m->next->prev = m->prev;
    
    // Aggiorna la testa della lista se stiamo rimuovendo il primo elemento
    if (primoLivello == m) {
        primoLivello = m->next;
    }
    
    if (livelloAttuale == m) {
        livelloAttuale = adiacente;
    }
    
    // Dealloca il livello (come richiesto)
    delete m;
    
    return adiacente;
}
