#include "Librerie.hpp"
#include "Tempo.hpp"

tempo::tempo() {}

//Fa iniziare il conto del tempo
void tempo::avvia(int t) {
    durata = t;
    tempo_rimasto = t;
    tempo_inizio = time(NULL);
}

//Fa scorrere il tempo
void tempo::diminuiscitempo() {
    time_t tempo_attuale = time(NULL);
    tempo_rimasto = durata - (tempo_attuale - tempo_inizio);
}

//Gestisce i momenti di blocco della partita, aggiunge quindi una pausa di tot secondi in modo tale da non far scorrere il tempo
void tempo::addpausa(int t) {
    tempo_inizio += t;
}

void tempo::aggiungiTempo(int t) {
    durata += t;
}
