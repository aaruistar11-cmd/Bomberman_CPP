#pragma once

#include "Librerie.hpp"
#include "Position.hpp"
#include "Config.hpp"
#include "Mappa.hpp"

class Enemy{
    protected:
        pos position;
        // n tipi di nemici (es. 3)
        int enemy_type;

        //per regolare la velocita in ms
        std::chrono::steady_clock::time_point last_update;
        Mappa* mappa; // Ora l'Enemy sa in che mappa si trova!
    
    public:
        // Passiamo y, x iniziali e la mappa
        Enemy(int _enemy_type, int startY, int startX, Mappa* _mappa);
        
        pos getPos();

        virtual void distruggi() = 0;

        virtual void move() = 0;

};