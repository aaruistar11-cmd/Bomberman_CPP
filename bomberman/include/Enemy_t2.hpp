#pragma once

#include "Librerie.hpp"
#include "Config.hpp"
#include "Enemy.hpp"
class Enemy_t2 : public Enemy {
protected:
  int dir;

public:
  Enemy_t2(int enemy_type, int startY, int startX, Mappa *mappa);

  // con ctime precisione solo al secondo
  void move() override;
  void distruggi() override { delete this; }
};