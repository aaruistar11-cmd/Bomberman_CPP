#include "Tempo.hpp"

tempo::tempo() {
    larghezza = 10;
    altezza = 3;
    getmaxyx(stdscr, maxy, maxx);
    maxx -= 15;
    win1 = NULL;
}

//Fa iniziare il conto del tempo
void tempo:: avvia(int t) {
    durata = t;
    tempo_rimasto = t;
    tempo_inizio = time(NULL);
}


//Disegna la finestra del tempo nella corretta posizione nello schermo
void tempo:: finestra() {
    getmaxyx(stdscr, maxy, maxx);
    maxx-=15;
    int y = 2;
    int x = maxx - larghezza - 5;
    if (x < 0) x = 0;
    if (win1 == NULL) {
        win1 = newwin(altezza, larghezza, y, x);
    }else {
        wresize(win1, altezza, larghezza);
        mvwin(win1, y, x);
    }
    box(win1, 0, 0);
    scrivitempo();
}

//Scrive il tempo attuale nella finestra
void tempo:: scrivitempo() {
    if (win1 == NULL) return;
    mvwprintw(win1, 1, 2, "%06d", tempo_rimasto);
    wrefresh(win1);
}

//Fa scorrere il tempo
void tempo:: diminuiscitempo() {
    // Rimosso il return se win1 == NULL per slegare la logica dall'interfaccia
    time_t tempo_attuale = time(NULL);
    tempo_rimasto = durata - (tempo_attuale - tempo_inizio);
    // Non chiamo scrivitempo() perché ora il tempo viene scritto dalla Mappa
}

//Gestisce i momenti di blocco della partita, aggiunge quindi una pausa di tot secondi in modo tale da non far scorrere il tempo
void tempo::addpausa(int t) {
    tempo_inizio += t;
}

void tempo::aggiungiTempo(int t) {
    durata += t;
}
