#pragma once

#include "Enemy.hpp"
#include <iostream>
#include <ctime>
#include "Config.hpp"
#include <ncurses.h>

class Enemy_t2 : public Enemy{
    int dir;
    
    public:
        Enemy_t2(int enemy_type, int startY, int startX, Mappa* mappa);

        //con ctime precisione solo al secondo
        void move() override;
};