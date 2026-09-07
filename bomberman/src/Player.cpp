#include "Librerie.hpp"
#include "Player.hpp"
Player::Player(int posx, int posy){
    position.x = posx;
    position.y = posy;
    lives = 3;   
    points = 0;   
    bomb_range = 1;   
    bonus_bomb_charges = 0;
    speed_ticks = 0;
    last_bomb_time = std::chrono::steady_clock::now() - std::chrono::seconds(5);
}

void Player::setPosition(int x,int y){
    // Non scriviamo più '@' sulla griglia logica per non corrompere gli oggetti sotto (es. bombe)
    // Il Gamemaster si occupa di disegnare il giocatore sopra la griglia!
    position.x = x;
    position.y = y;
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

int Player::getX(){ return position.x; }

int Player::getY(){ return position.y; }

int Player::getLives(){ return lives; }

int Player::looseLife() {
        lives -= 1;
        return lives;
    }

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