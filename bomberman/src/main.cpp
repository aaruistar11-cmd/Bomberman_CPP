#include "Librerie.hpp"
#include "Gamemaster.hpp"

int main() {
    srand(time(NULL)); // Seme per la generazione casuale della mappa

    initscr();
    resize_term(0, 0);
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    
    // Inizializzazione di TUTTI i colori
    init_pair(1, COLOR_RED, COLOR_BLACK);      // UI 
    init_pair(2, COLOR_BLUE, COLOR_BLACK);     // Player
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);   // Bombe
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);  // Esplosioni
    init_pair(5, COLOR_BLACK, COLOR_WHITE);    // Muri Solidi (Bianco)
    init_pair(6, COLOR_BLACK, COLOR_CYAN);     // Casse (Grigio/Cyan)

    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE); // FALSE nel menu, diventerà TRUE in partita
    
    Gamemaster game;
    game.run();
    
    endwin();
    return 0;
}