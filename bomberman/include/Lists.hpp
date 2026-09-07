
#pragma once

#include "Librerie.hpp"
#include "Bomb.hpp"
#include "Enemy.hpp"
#include "Item.hpp"

struct bomb_node{
    Bomb bomb;
    bomb_node *next;
};

typedef bomb_node *bnode;

//Puntaotre della classe enemy perchè è una classe astratta
struct enemy_node{
    Enemy *en;
    enemy_node *next;
};

typedef enemy_node *enode;

struct item_node {
    Item *it;
    item_node *next;
};

typedef item_node *inode;

