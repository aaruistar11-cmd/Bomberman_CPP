#include "Enemy_t3.hpp"

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::time_point;

Enemy_t3::Enemy_t3(int enemy_type, int startY, int startX, Mappa* mappa)
    : Enemy(enemy_type, startY, startX, mappa) {
    dirY = 1;
    dirX = 1;
}

void Enemy_t3::move(){
    time_point<steady_clock> curr_time = steady_clock::now();
    long long time_diff = duration_cast<milliseconds>(curr_time - last_update).count();

    if(time_diff >= 150){
        int newY = position.y + dirY;
        int newX = position.x + dirX;

        // Se urta sull'asse Y, inverte la direzione Y (rimbalzo semplice)
        if (mappa->getCella(newY, position.x) != ' ') {
            dirY = -dirY;
            newY = position.y + dirY;
        }
        // Se urta sull'asse X, inverte la direzione X
        if (mappa->getCella(position.y, newX) != ' ') {
            dirX = -dirX;
            newX = position.x + dirX;
        }

        // Se dopo i rimbalzi la cella finale è vuota, si muove.
        // Altrimenti (es. angolo interno chiuso), sceglie una nuova diagonale a caso.
        if (mappa->getCella(newY, newX) == ' ') {
            position.y = newY;
            position.x = newX;
        } else {
            dirY = (rand() % 2 == 0) ? 1 : -1;
            dirX = (rand() % 2 == 0) ? 1 : -1;
        }

        last_update = curr_time;
    }
}