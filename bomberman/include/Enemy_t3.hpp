#pragma once

#include "Librerie.hpp"
#include "Config.hpp"
#include "Enemy.hpp"
class Enemy_t3 : public Enemy {
protected:
  int dirY;
  int dirX;

public:
  Enemy_t3(int enemy_type, int startY, int startX, Mappa *mappa);

  void move() override;
  void distruggi() override { delete this; }
};