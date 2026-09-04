#pragma once


#include <iostream>
#include "Position.hpp"
//#include <ctime>
#include <chrono>
#include "Config.hpp"
#include <ncurses.h>
#include "Mappa.hpp" // Aggiunto!



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
        Enemy(int enemy_type, int startY, int startX, Mappa* mappa);

        virtual ~Enemy();
        
        pos getPos();

        virtual void move() = 0;

};