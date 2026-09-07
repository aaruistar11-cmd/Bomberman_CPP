#pragma once

#include "Librerie.hpp"
#ifdef _WIN32
#define getmouse nc_getmouse
#endif

class Schermo {
public:
    bool controllaDimensione(int MIN_X, int MIN_Y);
};
