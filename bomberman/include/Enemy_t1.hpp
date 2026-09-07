#pragma once

#include "Librerie.hpp"
#include "Config.hpp"
#include "Enemy.hpp"
class Enemy_t1 : public Enemy {
protected:
  int dir; // 0=su, 1=giu, 2=sinistra, 3=destra

public:
  Enemy_t1(int enemy_type, int startY, int startX, Mappa *mappa);

  // con ctime precisione solo al secondo
  void move() override;
  void distruggi() override { delete this; }
};