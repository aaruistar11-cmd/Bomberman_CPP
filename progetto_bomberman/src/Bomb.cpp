#include <ncurses.h>
#include "Bomb.hpp"

using std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;



#include "Bomb.hpp"

using std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;

Bomb::Bomb(int _y, int _x, int _range, Mappa* mappa){
    p.y = _y;
    p.x = _x;
    range = _range;
    this->mappa = mappa;
    state = COUNTING;
    start_time = steady_clock::now();

    define_hit_blocks();
    
    // Invece di mvaddch('X'), scriviamo 'B' (bomba innescata) nella Mappa
    mappa->setCella(_y, _x, 'B');
}

void Bomb::define_hit_blocks(){
    total_hit_blocks = 0;
    hit_blocks[total_hit_blocks++] = {p.y, p.x};

    // Propagazione in Su (si ferma ai muri solidi '#')
    for(int i = 1; i <= range; i++){
        if (mappa->getCella(p.y - i, p.x) == '#') break;
        hit_blocks[total_hit_blocks++] = {p.y - i, p.x};
    }
    // Giu
    for(int i = 1; i <= range; i++){
        if (mappa->getCella(p.y + i, p.x) == '#') break;
        hit_blocks[total_hit_blocks++] = {p.y + i, p.x};
    }
    // Sinistra (fissato bug di Lollo che usava -1 invece di -i)
    for(int i = 1; i <= range; i++){
        if (mappa->getCella(p.y, p.x - i) == '#') break;
        hit_blocks[total_hit_blocks++] = {p.y, p.x - i};
    }
    // Destra
    for(int i = 1; i <= range; i++){
        if (mappa->getCella(p.y, p.x + i) == '#') break;
        hit_blocks[total_hit_blocks++] = {p.y, p.x + i};
    }
}

void Bomb::update(){
    time_point<steady_clock> curr_time = steady_clock::now();

    if(state == COUNTING){
        long long time_diff = duration_cast<seconds>(curr_time - start_time).count();
        if(time_diff >= 3){
            state = EXPLODING;
            explosion_time = curr_time;
            
            // Togliamo la 'B' visiva dal centro della matrice
            mappa->setCella(p.y, p.x, ' ');
            
            // La distruzione logica delle casse (%) è ora delegata al Gamemaster 
            // per permettere un'assegnazione corretta dei punti!
        }
    }
    else if(state == EXPLODING){
        long long time_diff = duration_cast<milliseconds>(curr_time - explosion_time).count();
        if(time_diff >= 200){
            state = FINISHED;
        }
    }
}

void Bomb::render(){
    // Il rendering (fiamme) ora è gestito dal Gamemaster con stampaEntita per evitare conflitti con la griglia!
}

void Bomb::clear_fire(){
    // Non facciamo nulla, le fiamme grafiche spariscono semplicemente quando lo stato cambia da EXPLODING a FINISHED.
}

BombState Bomb::getState(){ return state; }
pos Bomb::getPos(){ return p; }
pos* Bomb::getHitBlocks(int &num_blocks) { 
    num_blocks = total_hit_blocks; 
    return hit_blocks; 
}

