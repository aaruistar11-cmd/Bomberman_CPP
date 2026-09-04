#include "Enemy.hpp"

using namespace std::chrono;

Enemy::Enemy(int enemy_type, int startY, int startX, Mappa* mappa){
    this->position.y = startY;
    this->position.x = startX;
    this->enemy_type = enemy_type;
    this->mappa = mappa;
    
    last_update = steady_clock::now();
}

Enemy::~Enemy(){
    // Niente più pulizia della matrice, i nemici sono "sospesi" sopra la mappa
}

pos Enemy::getPos(){ 
    return position; 
}
