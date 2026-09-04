#include "Player.hpp"
#include <ncurses.h>


Player::Player(int posx, int posy){
    this->position.x = posx;
    this->position.y = posy;
    this->lives = 3;   
    this->points = 0;   
    this->bomb_range = 1;   
    this->bonus_bomb_charges = 0;
    this->speed_ticks = 0;
    this->last_bomb_time = std::chrono::steady_clock::now() - std::chrono::seconds(5);
}

void Player::setPosition(int x,int y){
    // Non scriviamo più '@' sulla griglia logica per non corrompere gli oggetti sotto (es. bombe)
    // Il Gamemaster si occupa di disegnare il giocatore sopra la griglia!
    this->position.x = x;
    this->position.y = y;
}

void Player::play(int ch, Mappa* mappa){
    int nuovaX = position.x;
    int nuovaY = position.y;

    switch(ch){
        case 'w':
            if (position.y > 0) nuovaY--;
            break;
        case 's':
            if (position.y < 19) nuovaY++; 
            break;
        case 'a':
            if (position.x > 0) nuovaX--;
            break;
        case 'd':
            if (position.x < 39) nuovaX++; 
            break;
        default:
            return;
    }

    // Controlliamo la collisione PRIMA di muoverci
    char cella = mappa->getCella(nuovaY, nuovaX);
    
    // Se la casella è vuota, ci muoviamo
    if (cella == ' ') {
        setPosition(nuovaX, nuovaY);
    }
}

int Player::getBombRange(){ return bomb_range; }

void Player::setBombRange(int r){ bomb_range = r; }

int Player::getX(){ return this->position.x; }

int Player::getY(){ return this->position.y; }

int Player::getLives(){ return lives; }

void Player::setLives(int _lives ){ lives = _lives; }

int Player::getPoints(){ return points; }

void Player::setPoints(int _points ){ points = _points; }

void Player::adddPoints(int amount ){ points += amount; }

int Player::looseLife() {
        lives -= 1;
        return lives;
    }

bool Player::isAlive() { return lives != 0; }

void Player::decrementSpeedTicks() {
    if (speed_ticks > 0) speed_ticks--;
}

bool Player::hasSpeedBonus() {
    return speed_ticks > 0;
}

bool Player::useBombCharge() {
    if (bonus_bomb_charges > 0) {
        bonus_bomb_charges--;
        return true;
    }
    return false;
}

void Player::addBonusBombCharges(int charges) {
    bonus_bomb_charges += charges;
}

void Player::addSpeedTicks(int ticks) {
    speed_ticks += ticks;
}

void Player::addLife() {
    if (lives < 3) lives++;
}

bool Player::canPlaceBomb() {
    auto now = std::chrono::steady_clock::now();
    long long diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_bomb_time).count();
    return diff > 1000; // 1 second cooldown
}

void Player::placedBomb() {
    last_bomb_time = std::chrono::steady_clock::now();
}