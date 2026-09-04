#include "Gamemaster.hpp"
#include "Player.hpp"
#include "Enemy_t1.hpp"
#include "Enemy_t2.hpp"
#include "Enemy_t3.hpp"
#include "Bomb.hpp"

Gamemaster::Gamemaster() {
    stato=STATO_MENU;
    oldH=0;
    oldW=0;
    ehead = nullptr;
    bhead = nullptr;
    ihead = nullptr;
}

//Gestisce il responsive del menu e della partita
void Gamemaster::responsive() {
    int h, w;
    getmaxyx(stdscr, h, w);
    if (h != oldH || w != oldW) {
        time_t ora_inizio_blocco = time(NULL);
        if (!schermo.controllaDimensione(56, 28)) {
            werase(stdscr);
            touchwin(stdscr);
            refresh();
        }else {
            int secondi_di_pausa = time(NULL) - ora_inizio_blocco;
            if (stato==STATO_PARTITA) {
                Tempo.addpausa(secondi_di_pausa);
            }
        }
        oldH = h;
        oldW = w;
        if (stato == STATO_MENU) menu.drawMenu();
        else if (stato == STATO_PARTITA) {
            // Mappa gestisce già il resize e l'UI integrata
            werase(stdscr);
        }
    }
}

//Fa iniziare il disegno del menu
void Gamemaster::startmenu() {
    schermo.controllaDimensione(56, 28);
    nodelay(stdscr, FALSE);
    menu.drawMenu();
    while (stato==STATO_MENU) {
        responsive();
        int ch = getch();
        if (ch==KEY_MOUSE){
            MEVENT event;
            if (getmouse(&event) == OK) {
                int butt=menu.controllaClick(event);
                if (butt==0) {
                    stato=STATO_PARTITA;
                }else if (butt==1) {
                    stato=STATO_CLASSIFICA;
                }else if (butt==2) {
                    stato=STATO_ESCI;
                }
            }
        }
    }
}

//Fa iniziare il disegno della classifica
void Gamemaster::startclassifica() {
    nodelay(stdscr, FALSE);
    classifica.Npunti();
    stato=STATO_MENU;
}

//Fa iniziare il disegno della parte finale
void Gamemaster::startfine() {
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    Fine.drawend();
    Fine.drawnome(Punti.puntif());
    stato=STATO_ESCI;
}

//Disegna e gestisce l'inizio della partita
#include "GestoreLivelli.hpp"

void Gamemaster::startpartita() {
    keypad(stdscr, TRUE);
    // nodelay rimosso perché timeout(100) fa già il suo lavoro e fa girare il gioco a 10 fps costanti
    timeout(100);
    Tempo.avvia(240); // Impostato a 240s come hai chiesto
    Punti.azzera();
    werase(stdscr);
    refresh();
    
    // -----------------------------------------------------
    // INTEGRAZIONE MOTORE DI GIOCO (Mappa e Livelli)
    // -----------------------------------------------------
    GestoreLivelli gestore;
    for (int i = 1; i <= 5; i++) {
        Mappa* nuovaMappa = new Mappa(i, rand());
        nuovaMappa->inizializzaGriglia(); // FONDAMENTALE: popola la matrice
        gestore.aggiungiLivello(nuovaMappa);
    }
    Mappa* mappaCorrente = gestore.getPrimoLivello();

    // Creazione del Giocatore alle coordinate iniziali (1,1)
    Player pl(1, 1);
    pl.setPosition(1, 1);
    
    // Spawna i nemici della prima mappa
    spawnNemici(mappaCorrente);

    while (stato==STATO_PARTITA) {
        // 1. GESTIONE FINESTRA E TEMPO
        responsive();
        Tempo.diminuiscitempo();
        pl.decrementSpeedTicks();
        
        if (Punti.puntif()>=1000) stato=STATO_FINE;
        else if (Tempo.tempo_rimasto<=0) stato=STATO_FINE;

        // 2. AGGIORNAMENTO LOGICO (Entità)
        aggiornaBombe();
        aggiornaNemici();
        
        // 3. RENDERING (Mappa + Entità)
        mappaCorrente->disegnaLayout(Punti.puntif(), Tempo.tempo_rimasto, pl.getLives());
        
        // 3a. Bombe ed esplosioni
        bnode currB = bhead;
        while(currB != nullptr){
            if (currB->bomb.getState() == COUNTING) {
                mappaCorrente->stampaEntita(currB->bomb.getPos().y, currB->bomb.getPos().x, 'B', 3);
            } else if (currB->bomb.getState() == EXPLODING) {
                int num_blocks;
                pos* hit_blocks = currB->bomb.getHitBlocks(num_blocks);
                
                for(int i = 0; i < num_blocks; i++) {
                    int fy = hit_blocks[i].y;
                    int fx = hit_blocks[i].x;
                    
                    if (mappaCorrente->getCella(fy, fx) == '%') {
                        int rand_val = rand() % 100;
                        if (rand_val < 5) {
                            Item* newItem = new Item(fy, fx, ITEM_LIFE);
                            inode tmp = new item_node{newItem, ihead};
                            ihead = tmp;
                        }
                        else if (rand_val < 20) {
                            Item* newItem = new Item(fy, fx, ITEM_RANGE);
                            inode tmp = new item_node{newItem, ihead};
                            ihead = tmp;
                        }
                        else if (rand_val < 35) {
                            Item* newItem = new Item(fy, fx, ITEM_SPEED);
                            inode tmp = new item_node{newItem, ihead};
                            ihead = tmp;
                        }
                        mappaCorrente->setCella(fy, fx, ' ');
                        Punti.addpunti(10);
                    }
                    
                    if (mappaCorrente->getCella(fy, fx) != '#') {
                        mappaCorrente->stampaEntita(fy, fx, '*', 5);
                        
                        // Collisione mortale col giocatore
                        if (pl.getY() == fy && pl.getX() == fx) {
                            if (pl.looseLife() == 0) stato = STATO_FINE;
                            else pl.setPosition(1, 1);
                        }
                        
                        // Collisione mortale coi nemici
                        enode prevE = nullptr;
                        enode currE = ehead;
                        while(currE != nullptr) {
                            if (currE->en->getPos().y == fy && currE->en->getPos().x == fx) {
                                Punti.addpunti(100);
                                enode delE = currE;
                                if(prevE == nullptr) ehead = currE->next;
                                else prevE->next = currE->next;
                                currE = currE->next;
                                delete delE->en;
                                delete delE;
                            } else {
                                prevE = currE;
                                currE = currE->next;
                            }
                        }
                    }
                }
            }
            currB = currB->next;
        }
        
        // 3b. Nemici (Disegno e collisione col giocatore)
        enode currE = ehead;
        
        // Progressione automatica: se non ci sono nemici, si rimuove questo livello
        if (currE == nullptr) {
            Punti.addpunti(500); // Bonus punti per livello completato
            Tempo.aggiungiTempo(120); // Bonus tempo
            
            Mappa* nuovaMappa = gestore.rimuoviLivello(mappaCorrente);
            
            if (nuovaMappa != nullptr) {
                mappaCorrente = nuovaMappa;
                pl.setPosition(1, 1);
                
                svuotaEntita(); // Pulisce items, bombe e vecchi nemici
                spawnNemici(mappaCorrente);
                werase(stdscr);
                
                currE = ehead; // Aggiorna il puntatore per il disegno
            } else {
                // Gioco completato, bonus punti in base al tempo rimasto (es. 10 punti per secondo)
                if (Tempo.tempo_rimasto > 0) Punti.addpunti(Tempo.tempo_rimasto * 10);
                stato = STATO_FINE; // Hai vinto, non ci sono più livelli
            }
        }
        
        while(currE != nullptr){
            mappaCorrente->stampaEntita(currE->en->getPos().y, currE->en->getPos().x, 'O', 1);
            if (currE->en->getPos().y == pl.getY() && currE->en->getPos().x == pl.getX()) {
                if (pl.looseLife() == 0) stato = STATO_FINE;
                else pl.setPosition(1, 1);
            }
            currE = currE->next;
        }
        
        // 3c. Items (Rendering e Pickup)
        inode currI = ihead;
        inode prevI = nullptr;
        while (currI != nullptr) {
            if (currI->it->getY() == pl.getY() && currI->it->getX() == pl.getX()) {
                currI->it->apply(&pl);
                
                inode delI = currI;
                if (prevI == nullptr) ihead = currI->next;
                else prevI->next = currI->next;
                currI = currI->next;
                
                delete delI->it;
                delete delI;
            } else {
                int color = 2; // Default SPEED
                if (currI->it->getType() == ITEM_RANGE) color = 1;
                else if (currI->it->getType() == ITEM_LIFE) color = 4; // Magenta for LIFE
                
                mappaCorrente->stampaEntita(currI->it->getY(), currI->it->getX(), currI->it->getSymbol(), color);
                
                prevI = currI;
                currI = currI->next;
            }
        }
        
        // 3d. Giocatore
        mappaCorrente->stampaEntita(pl.getY(), pl.getX(), '@', 2);
        
        refresh(); // Flusha a schermo TUTTO quanto insieme

        // 4. INPUT E MOVIMENTO (Bloccante per 100ms tramite timeout)
        int t=getch();
        if (t!=ERR) {
            if (t == 'n' && mappaCorrente->next != nullptr) {
                int nemiciRimasti = 0;
                for (enode e = ehead; e != nullptr; e = e->next) nemiciRimasti++;
                mappaCorrente->nemici_rimasti = nemiciRimasti;
                
                mappaCorrente = mappaCorrente->next;
                pl.setPosition(1, 1);
                svuotaEntita();
                spawnNemici(mappaCorrente);
                werase(stdscr);
            } else if (t == 'p' && mappaCorrente->prev != nullptr) {
                int nemiciRimasti = 0;
                for (enode e = ehead; e != nullptr; e = e->next) nemiciRimasti++;
                mappaCorrente->nemici_rimasti = nemiciRimasti;
                
                mappaCorrente = mappaCorrente->prev;
                pl.setPosition(1, 1);
                svuotaEntita();
                spawnNemici(mappaCorrente);
                werase(stdscr);
            }
            
            if (t == 'x') {
                if (pl.canPlaceBomb()) {
                    int raggio = pl.getBombRange();
                    if (pl.useBombCharge()) raggio += 2; // Raggio esteso se ha bonus
                    bnode tmp = new bomb_node{Bomb(pl.getY(), pl.getX(), raggio, mappaCorrente), bhead};
                    bhead = tmp;
                    pl.placedBomb();
                }
            } else {
                pl.play(t, mappaCorrente);
                // Se ha il bonus velocità, processa un altro input (movimento doppio)
                if (pl.hasSpeedBonus()) {
                    int t2 = getch();
                    if (t2 != ERR) {
                        if (t2 == 'x') {
                            if (pl.canPlaceBomb()) {
                                int raggio2 = pl.getBombRange();
                                if (pl.useBombCharge()) raggio2 += 2;
                                bnode tmp = new bomb_node{Bomb(pl.getY(), pl.getX(), raggio2, mappaCorrente), bhead};
                                bhead = tmp;
                                pl.placedBomb();
                            }
                        } else {
                            pl.play(t2, mappaCorrente);
                        }
                    }
                }
            }
        }
    }
    
    // Deallocazione manuale (come da vincoli accademici)
    svuotaEntita();
    Mappa* temp = gestore.getPrimoLivello();
    while (temp != nullptr) {
        Mappa* daCancellare = temp;
        temp = temp->next;
        delete daCancellare;
    }
    
    nodelay(stdscr, FALSE); // Ripristino nodelay per i menu successivi
    werase(stdscr);
    touchwin(stdscr);
    refresh();
}

// Svuota in modo sicuro le liste di entità (come da distruttore di Game di Lollo)
void Gamemaster::svuotaEntita() {
    bnode currB = bhead;
    while(currB != nullptr) {
        bnode next = currB->next;
        delete currB;
        currB = next;
    }
    bhead = nullptr;

    enode currE = ehead;
    while(currE != nullptr) {
        enode next = currE->next;
        delete currE->en;
        delete currE;
        currE = next;
    }
    ehead = nullptr;

    inode currI = ihead;
    while(currI != nullptr) {
        inode next = currI->next;
        delete currI->it;
        delete currI;
        currI = next;
    }
    ihead = nullptr;
}














// Trova spazi vuoti e li popola con Nemici
void Gamemaster::spawnNemici(Mappa* mappa) {
    svuotaEntita(); // Pulisce i nemici vecchi prima di spawnare quelli nuovi
    int numNemici = mappa->nemici_rimasti;
    int piazzati = 0;
    while (piazzati < numNemici) {
        int y = (rand() % (20 - 2)) + 1;
        int x = (rand() % (40 - 2)) + 1;
        if (mappa->getCella(y, x) == ' ' && (y > 4 || x > 4)) {
            int tipo = (rand() % 3) + 1; 
            Enemy* newEnemy = nullptr;
            if (tipo == 1) newEnemy = new Enemy_t1(tipo, y, x, mappa);
            else if (tipo == 2) newEnemy = new Enemy_t2(tipo, y, x, mappa);
            else if (tipo == 3) newEnemy = new Enemy_t3(tipo, y, x, mappa);
            
            enode tmp = new enemy_node{newEnemy, ehead};
            ehead = tmp;
            piazzati++;
        }
    }
}

void Gamemaster::aggiornaBombe() {
    bnode curr = bhead;
    bnode prev = nullptr;

    while(curr != nullptr){
        curr->bomb.update();
        curr->bomb.render();
        
        if(curr->bomb.getState() == FINISHED){
            bnode del_bomb = curr;
            if(prev == nullptr) bhead = curr->next;
            else prev->next = curr->next;
            
            curr = curr->next;
            delete del_bomb;
        }else{
            prev = curr;
            curr = curr->next;
        }
    }
}

void Gamemaster::aggiornaNemici() {
    enode curr = ehead;
    while(curr != nullptr){
        curr->en->move();
        curr = curr->next;
    }
}

//Fa iniziare la partita
void Gamemaster::run() {
    getmaxyx(stdscr, oldH, oldW);
    while (stato!=STATO_ESCI) {
        switch (stato) {
            case STATO_MENU:
                startmenu();
                break;
            case STATO_PARTITA:
                startpartita();
                break;
            case STATO_CLASSIFICA:
                startclassifica();
                break;
            case STATO_FINE:
                startfine();
                break;
            case STATO_ESCI:
                break;
        }
    }
    clear();
    refresh();
    getch();
    endwin();
}