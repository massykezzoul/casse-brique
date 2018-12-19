#include "window.h"
#include "Body.h"
#include "player.h"
#include "brick.h"
#include <unistd.h>

int main () {
  startProgramX();
  Window* w = new Window(30, 50, 1, 1, '+');
  w->setCouleurBordure(WBLACK);
  w->setCouleurFenetre(BWHITE);
  Body::SetWindow(w);
  Player* p = new Player();
  Brick::set_player(p);
  Brick b1(CARRE, 1, 10, 1, 1);
  Brick b2(CARRE, 1, 10, 5, 1);
  Brick b3(CARRE, 1, 10, 9, 1);
  while (1) {
    w->clear();
    Body::AllUpdate();
    usleep(50000);
  }
  delete w;
  delete p;
  stopProgramX();
}
