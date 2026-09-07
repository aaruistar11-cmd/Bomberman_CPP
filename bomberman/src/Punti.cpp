#include "Librerie.hpp"
#include "Punti.hpp"
punti::punti() {punteggio=0;};

//Restituisce punteggio
int punti:: puntif() {return punteggio;}

//Azzera il punteggio
void punti::azzera() {punteggio=0;};

void punti::addpunti(int p) { punteggio += p; }
