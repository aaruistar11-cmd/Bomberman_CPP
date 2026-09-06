#ifndef BOMBERMAN_GAMEMASTER_H
#define BOMBERMAN_GAMEMASTER_H
using namespace std;
#include "Classifica.hpp"
#include "fine.hpp"
#include "Menu.hpp"
#include "Punti.hpp"
#include "Tempo.hpp"
#include "Schermo.hpp"
#include <ctime>
#include "GestoreLivelli.hpp"

enum StatoGioco {
    STATO_MENU, STATO_PARTITA, STATO_FINE, STATO_ESCI, STATO_CLASSIFICA
};

#include "Lists.hpp"

class Gamemaster {
protected:
    StatoGioco stato;
    Menu menu;
    Classifica classifica;
    fine Fine;
    punti Punti;
    tempo Tempo;
    Schermo schermo;
    
    int oldH;
    int oldW;
    
    // Liste per Nemici e Bombe (da Lollo)
    enode ehead;
    bnode bhead;
    inode ihead;
    
    void responsive();
    void svuotaEntita();
    void spawnNemici(Mappa* mappa);
    void aggiornaNemici();
    void aggiornaBombe();
    
public:
    Gamemaster();
    void startmenu();
    void startclassifica();
    void startfine();
    void startpartita();
    void run();
};
#endif
