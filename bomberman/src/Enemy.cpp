#include "Librerie.hpp"
#include "Enemy.hpp"

using namespace std::chrono;

Enemy::Enemy(int _enemy_type, int startY, int startX, Mappa* _mappa){
    position.y = startY;
    position.x = startX;
    enemy_type = _enemy_type;
    mappa = _mappa;
    
    last_update = steady_clock::now();
}

pos Enemy::getPos(){ 
    return position; 
}
