#pragma once



#include <iostream>
#include <chrono>
#include "Position.hpp"
#include "Mappa.hpp"


enum BombState { COUNTING, EXPLODING, FINISHED };

class Bomb{
    int range;
    pos p;
    pos hit_blocks[17];
    int total_hit_blocks;
    BombState state;
    Mappa* mappa;

    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point explosion_time;

    void define_hit_blocks();
    

    public:
        Bomb(int y, int x, int range, Mappa* mappa);

        //Crea un array di 5 pos (y, x) dove la bomba fa danno
        //Bisogna poi capire se ci sono dei mustri da distruggere, nemici ecc.
        //Il comportamente delle bombe puo essere modificato dagli item ecc.
        

        //colora i blocchi di hit di rosso
        void update();

        void render();

        void clear_fire();

        BombState getState();

        pos getPos();
        
        pos* getHitBlocks(int &num_blocks);

};
