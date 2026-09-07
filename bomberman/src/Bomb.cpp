#include "Librerie.hpp"
#include "Bomb.hpp"
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::steady_clock;
using std::chrono::time_point;

Bomb::Bomb(int _y, int _x, int _range, Mappa *_mappa) {
  p.y = _y;
  p.x = _x;
  range = _range;
  mappa = _mappa;
  state = COUNTING;
  start_time = steady_clock::now();
  
  define_hit_blocks();
  mappa->setCella(_y, _x, 'B');
}

void Bomb::define_hit_blocks() {
  total_hit_blocks = 0;
  hit_blocks[total_hit_blocks++] = {p.y, p.x};

  // Esplosione in su
  for (int i = 1; i <= range; i++) {
    if (mappa->getCella(p.y - i, p.x) == '#')
      break;
    hit_blocks[total_hit_blocks++] = {p.y - i, p.x};
  }
  // Giu
  for (int i = 1; i <= range; i++) {
    if (mappa->getCella(p.y + i, p.x) == '#')
      break;
    hit_blocks[total_hit_blocks++] = {p.y + i, p.x};
  }
  // Sinistra
  for (int i = 1; i <= range; i++) {
    if (mappa->getCella(p.y, p.x - i) == '#')
      break;
    hit_blocks[total_hit_blocks++] = {p.y, p.x - i};
  }
  // Destra
  for (int i = 1; i <= range; i++) {
    if (mappa->getCella(p.y, p.x + i) == '#')
      break;
    hit_blocks[total_hit_blocks++] = {p.y, p.x + i};
  }
}

void Bomb::update() {
  time_point<steady_clock> curr_time = steady_clock::now();

  if (state == COUNTING) {
    long long time_diff =
        duration_cast<seconds>(curr_time - start_time).count();
    if (time_diff >= 3) {
      state = EXPLODING;
      explosion_time = curr_time;

      // Togliamo la 'B' visiva dal centro della matrice
      mappa->setCella(p.y, p.x, ' ');

      // La distruzione logica delle casse (%) è ora delegata al Gamemaster
      // per permettere un'assegnazione corretta dei punti!
    }
  } else if (state == EXPLODING) {
    long long time_diff =
        duration_cast<milliseconds>(curr_time - explosion_time).count();
    if (time_diff >= 200) {
      state = FINISHED;
    }
  }
}

BombState Bomb::getState() { return state; }
pos Bomb::getPos() { return p; }
pos *Bomb::getHitBlocks(int &num_blocks) {
  num_blocks = total_hit_blocks;
  return hit_blocks;
}
