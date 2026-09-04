#pragma once

#include "Enemy.hpp"
#include <iostream>
#include <ctime>
#include "Config.hpp"
#include <ncurses.h>

class Enemy_t3 : public Enemy{
    int dirY;
    int dirX;

    public:
        Enemy_t3(int enemy_type, int startY, int startX, Mappa* mappa);

        void move() override;
};