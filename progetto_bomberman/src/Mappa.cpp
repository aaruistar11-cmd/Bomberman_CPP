#include "Mappa.hpp"
#include <ctime>

// ============================================================================
// COSTRUTTORE E INIZIALIZZAZIONE
// ============================================================================
Mappa::Mappa(int livello, unsigned int semeBase) {
    altezza = 20;
    larghezza = 40;
    idLivello = livello;
    nemici_rimasti = livello * 2;
    
    // Variazione del seme per evitare mappe identiche se generate nello stesso istante
    seme_casuale = semeBase + (livello * 9999);
    
    next = 0;
    prev = 0;
}

int Mappa::generaCasuale() {
    seme_casuale = seme_casuale * 1103515245 + 12345;
    unsigned int valoreTemporaneo = (unsigned int)(seme_casuale / 65536);
    return valoreTemporaneo % 32768;
}

// ============================================================================
// GENERAZIONE PROCEDURALE GRIGLIA
// ============================================================================
void Mappa::inizializzaGriglia() {
    // ------------------------------------------------------------------------
    // GENERAZIONE CASUALE FEDELE AL VIDEO DEL PROFESSORE
    // I muri solidi e le casse sono distribuiti in modo puramente random
    // per creare cluster irregolari e corridoi asimmetrici.
    // ------------------------------------------------------------------------
    int densitaCasse = 0;
    int densitaSolidi = 0;
    
    switch (idLivello) {
        case 1: // Livello 1: Easy (ma leggermente più impegnativo)
            densitaSolidi = 6;
            densitaCasse = 13;
            break;
        case 2: // Livello 2: Medio
            densitaSolidi = 7;
            densitaCasse = 15;
            break;
        case 3: // Livello 3: Intermedio
            densitaSolidi = 10;
            densitaCasse = 20;
            break;
        case 4: // Livello 4: Impegnativo
            densitaSolidi = 12;
            densitaCasse = 25;
            break;
        case 5: // Livello 5: Difficile (ma non impossibile, c'è spazio di manovra)
            densitaSolidi = 15;
            densitaCasse = 30;
            break;
        default:
            densitaSolidi = 7;
            densitaCasse = 15;
            break;
    }

    for (int riga = 0; riga < altezza; riga++) {
        for (int col = 0; col < larghezza; col++) {
            // Muri esterni fissi
            if (riga == 0 || riga == altezza - 1 || col == 0 || col == larghezza - 1) {
                griglia[riga][col] = '#'; 
            } 
            else {
                // Nessuna griglia geometrica: tutto è guidato dal caso
                int percentuale = generaCasuale() % 100;
                
                // Muro solido
                if (percentuale < densitaSolidi) {
                    griglia[riga][col] = '#';
                } 
                // Cassa distruttibile
                else if (percentuale < densitaSolidi + densitaCasse) {
                    griglia[riga][col] = '%';
                } 
                // Spazio vuoto
                else {
                    griglia[riga][col] = ' '; 
                }
            }
        }
    }
    
    // Spazio iniziale per il giocatore in alto a sinistra
    griglia[1][1] = ' '; // Vuoto, il giocatore ci starà sopra
    griglia[1][2] = ' '; 
    griglia[2][1] = ' '; 
    griglia[2][2] = ' '; 
}

// ============================================================================
// RENDERING DEL LAYOUT
// ============================================================================
// Disegna in modo separato la cornice UI (sottile) e il labirinto.
// Implementa accuratamente la differenza di texture e colore per le mura.
// ============================================================================
void Mappa::disegnaLayout(int punti, int tempo, int vite) {
    erase();
    
    // Dimensioni della scatola UI esterna (NON il labirinto)
    int larghezzaBox = larghezza + 14; 
    int altezzaBox = altezza + 6;
    
    int inizioY = (LINES - altezzaBox) / 2;
    int inizioX = (COLS - larghezzaBox) / 2;
    if (inizioY < 0) inizioY = 0;
    if (inizioX < 0) inizioX = 0;
    
    // Attiviamo il colore bianco (senza BOLD) per le linee sottili della UI
    attron(COLOR_PAIR(4));
    
    // ==================================================
    // 1. CORNICE UI ESTERNA SOTTILE (Linee)
    // ==================================================
    move(inizioY, inizioX);
    addch(ACS_ULCORNER); 
    
    int cifreLivello = 1;
    int copiaLivello = idLivello;
    while (copiaLivello > 9) { cifreLivello++; copiaLivello /= 10; }
    int lunghezzaTitolo = 23 + cifreLivello; // " BOMBERMAN ASCII - LV %d "
    
    int trattiniSinistra = (larghezzaBox - 2 - lunghezzaTitolo) / 2;
    int trattiniDestra = larghezzaBox - 2 - lunghezzaTitolo - trattiniSinistra;
    
    for (int i = 0; i < trattiniSinistra; i++) {
        addch(ACS_HLINE);
    }
    
    attron(A_BOLD);
    printw(" BOMBERMAN ASCII - LV %d ", idLivello);
    attroff(A_BOLD);
    
    for (int i = 0; i < trattiniDestra; i++) {
        addch(ACS_HLINE);
    }
    addch(ACS_URCORNER); 
    
    // Print vite at the top right
    attron(A_BOLD);
    mvprintw(inizioY, inizioX + larghezzaBox + 2, "vita/e : %d", vite);
    mvprintw(inizioY + 2, inizioX + larghezzaBox + 2, "[n] : Prossimo Livello");
    mvprintw(inizioY + 3, inizioX + larghezzaBox + 2, "[p] : Livello Precedente");
    attroff(A_BOLD);
    
    for (int rigaBox = 1; rigaBox < altezzaBox - 1; rigaBox++) {
        move(inizioY + rigaBox, inizioX);
        addch(ACS_VLINE); 
        
        move(inizioY + rigaBox, inizioX + larghezzaBox - 1);
        addch(ACS_VLINE); 
    }
    
    move(inizioY + altezzaBox - 1, inizioX);
    addch(ACS_LLCORNER); 
    
    int cifrePunti = 1;
    int copiaPunti = punti;
    if (copiaPunti < 0) { cifrePunti++; copiaPunti = -copiaPunti; }
    while (copiaPunti > 9) { cifrePunti++; copiaPunti /= 10; }
    
    int cifreTempo = 1;
    int copiaTempo = tempo;
    if (copiaTempo < 0) { cifreTempo++; copiaTempo = -copiaTempo; }
    while (copiaTempo > 9) { cifreTempo++; copiaTempo /= 10; }
    
    int lunghezzaFooter = 8 + cifrePunti + 9 + cifreTempo;
    
    int footerSinistra = (larghezzaBox - 2 - lunghezzaFooter) / 2;
    int footerDestra = larghezzaBox - 2 - lunghezzaFooter - footerSinistra;
    
    for (int i = 0; i < footerSinistra; i++) {
        addch(ACS_HLINE);
    }
    
    attron(A_BOLD);
    printw("points: %d   time: %d", punti, tempo);
    attroff(A_BOLD);
    
    for (int i = 0; i < footerDestra; i++) {
        addch(ACS_HLINE);
    }
    addch(ACS_LRCORNER); 
    
    attroff(COLOR_PAIR(4));
    
    // ==================================================
    // 2. MATRICE DEL GIOCO E MURA INTERNE
    // ==================================================
    int offsetLabirintoY = (altezzaBox - altezza) / 2;
    int offsetLabirintoX = (larghezzaBox - larghezza) / 2;
    
    for (int riga = 0; riga < altezza; riga++) {
        for (int col = 0; col < larghezza; col++) {
            
            move(inizioY + offsetLabirintoY + riga, inizioX + offsetLabirintoX + col);
            char blocco = griglia[riga][col];
            
            if (blocco == 'B') {
                // Bomba (Yellow)
                attron(COLOR_PAIR(3) | A_BOLD);
                printw("¤");
                attroff(COLOR_PAIR(3) | A_BOLD);
            } 
            else if (blocco == '%') {
                // Muro Distruttibile: Casse
                attron(COLOR_PAIR(4) | A_DIM);
                addch(ACS_CKBOARD); 
                attroff(COLOR_PAIR(4) | A_DIM);
            } 
            else if (blocco == '#') {
                // Muri Solidi Indistruttibili
                attron(COLOR_PAIR(5));
                addch(' ');
                attroff(COLOR_PAIR(5));
            } 

            else {
                addch(' ');
            }
        }
    }
    // Il refresh verrà chiamato dal Gamemaster alla fine!
}

// ============================================================================
// STAMPA ENTITA' DINAMICHE (Player, Nemici, Fiamme)
// ============================================================================
void Mappa::stampaEntita(int y, int x, char c, int color_pair) {
    int larghezzaBox = larghezza + 14; 
    int altezzaBox = altezza + 6;
    
    int inizioY = (LINES - altezzaBox) / 2;
    int inizioX = (COLS - larghezzaBox) / 2;
    if (inizioY < 0) inizioY = 0;
    if (inizioX < 0) inizioX = 0;
    
    int offsetLabirintoY = (altezzaBox - altezza) / 2;
    int offsetLabirintoX = (larghezzaBox - larghezza) / 2;
    
    attron(COLOR_PAIR(color_pair) | A_BOLD);
    mvaddch(inizioY + offsetLabirintoY + y, inizioX + offsetLabirintoX + x, c);
    attroff(COLOR_PAIR(color_pair) | A_BOLD);
}

// ============================================================================
// GESTIONE DELLE COLLISIONI (Interfaccia per il Giocatore)
// ============================================================================
char Mappa::getCella(int y, int x) {
    // Evitiamo segmentation fault se il giocatore cerca di uscire dai limiti
    if (y >= 0 && y < altezza && x >= 0 && x < larghezza) {
        return griglia[y][x];
    }
    return '#'; // Fuori dai bordi è considerato muro di cemento
}

void Mappa::setCella(int y, int x, char valore) {
    if (y >= 0 && y < altezza && x >= 0 && x < larghezza) {
        griglia[y][x] = valore;
    }
}
