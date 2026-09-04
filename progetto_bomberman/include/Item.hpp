#pragma once

#include "Position.hpp"

class Player; // Forward declaration

enum ItemType {
    ITEM_RANGE,
    ITEM_SPEED,
    ITEM_LIFE
};

class Item {
private:
    pos position;
    ItemType type;

public:
    Item(int y, int x, ItemType t);
    
    int getY();
    int getX();
    ItemType getType();
    char getSymbol();

    void apply(Player* p);
};
