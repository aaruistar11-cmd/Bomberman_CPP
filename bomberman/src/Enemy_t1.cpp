#include "Librerie.hpp"
#include "Enemy_t1.hpp"

using std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

Enemy_t1::Enemy_t1(int enemy_type, int startY, int startX, Mappa* mappa) 
    : Enemy(enemy_type, startY, startX, mappa) {
    dir = rand() % 4; // Direzione iniziale casuale
}

void Enemy_t1::move(){
    time_point<steady_clock> curr_time = steady_clock::now();
    long long time_diff = duration_cast<milliseconds>(curr_time - last_update).count();

    if(time_diff >= 300){
        int dy = 0, dx = 0;
        if(dir == 0) dy = -1;
        else if(dir == 1) dy = 1;
        else if(dir == 2) dx = -1;
        else if(dir == 3) dx = 1;

        int nuovaY = position.y + dy;
        int nuovaX = position.x + dx;

        if (mappa->getCella(nuovaY, nuovaX) == ' ') {
            position.y = nuovaY;
            position.x = nuovaX;
        } else {
            // Se sbatte, prova una nuova direzione casuale
            dir = rand() % 4;
        }

        last_update = curr_time;
    }
}