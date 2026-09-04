#pragma once


#include "Enemy.hpp"
#include <iostream>
#include <chrono>
#include "Config.hpp"
#include <ncurses.h>

class Enemy_t1 : public Enemy{private:
    int dir; // 0=su, 1=giu, 2=sinistra, 3=destra

    public:
        Enemy_t1(int enemy_type, int startY, int startX, Mappa* mappa);

        //con ctime precisione solo al secondo
        void move() override;
};