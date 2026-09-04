
#pragma once


#include "Position.hpp"
#include "Config.hpp"
#include "Mappa.hpp"
#include <chrono>

class Player{
    pos position;
    int points;
    int lives;
    int bomb_range;
    int bonus_bomb_charges;
    int speed_ticks;
    std::chrono::steady_clock::time_point last_bomb_time;

    public:
        Player(int posx, int posy);

        void setPosition(int x, int y);

        // Ora il player si muove calcolando le collisioni reali sulla mappa!
        void play(int ch, Mappa* mappa);
        
        //Getters e setters utili 

        int getBombRange();
        void setBombRange(int r);

        int getX();
        int getY();

        int getLives();
        void setLives(int _lives );

        int getPoints();
        void setPoints(int _points );

        void adddPoints(int amount );

        int looseLife();

        bool isAlive();

        void decrementSpeedTicks();
        bool hasSpeedBonus();
        bool useBombCharge();

        void addBonusBombCharges(int charges);
        void addSpeedTicks(int ticks);
        void addLife();

        bool canPlaceBomb();
        void placedBomb();
};

