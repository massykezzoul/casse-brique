#include "window.h"
#include "Body.h"
#include "player.h"
#include "brick.h"
#include "Terrain.h"
#include "ball.h"
#include <unistd.h>

int main () {
  startProgramX();
  //Initialisation
  Terrain t(60, 1, 50, 25);
  Player* p = new Player();
  Brick::set_player(p);
  //Niveau
  Brick b1(CARRE, 1, 10, 25, 5);
  Brick b2(CARRE, 1, 10, 5, 5);
  Brick b3(CARRE, 1, 10, 9, 5);
  Brick b4(CARRE, 1, 10, 13, 5);
  Brick b5(CARRE, 1, 10, 17, 5);
  Brick b6(CARRE, 1, 10, 21, 5);
  //Balle
  Ball ball(10, 10, 1.0, 0.5,WCYAN);
  //Jeu
  while (1) {
    t.Update();
    //p->print();
    p->print(ball);
    usleep(50000);
  }
  stopProgramX();
}
