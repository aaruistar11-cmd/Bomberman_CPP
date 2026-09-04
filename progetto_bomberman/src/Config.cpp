#include "Config.hpp"
#include <ncurses.h>


int SCREEN_H = 0;
int SCREEN_W = 0;

bool cancel_pos(int y, int x){
    chtype c = mvinch(y, x);
    if(((c & A_CHARTEXT) == 'X') || ((PAIR_NUMBER(c & A_COLOR) == 2) && (c & A_REVERSE))) 
        return false;
    return true;
};