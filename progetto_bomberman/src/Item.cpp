#include "Item.hpp"
#include "Player.hpp"

Item::Item(int y, int x, ItemType t) {
    this->position.y = y;
    this->position.x = x;
    this->type = t;
}

int Item::getY() { return position.y; }
int Item::getX() { return position.x; }
ItemType Item::getType() { return type; }

char Item::getSymbol() {
    if (type == ITEM_RANGE) return 'R';
    if (type == ITEM_SPEED) return 'S';
    if (type == ITEM_LIFE) return 'L';
    return '?';
}

void Item::apply(Player* p) {
    if (type == ITEM_RANGE) {
        p->addBonusBombCharges(3);
    } else if (type == ITEM_SPEED) {
        p->addSpeedTicks(50);
    } else if (type == ITEM_LIFE) {
        p->addLife();
    }
}
