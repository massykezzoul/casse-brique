#include "window.h"
#include "Body.h"
#include "player.h"
#include "brick.h"
#include "Terrain.h"
#include "ball.h"
#include "raquette.h"
#include <unistd.h>

/*
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
*/
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
  Raquette rq(10,20,1,20,WGREEN);
  Ball ball(10, 10, 1.0, 45,WCYAN);
  //Raquette
  //Jeu
  int c=0;

  while (c != 'q')  {
    t.Update();
    p->print();
    
    c=0;
    c=getch();
    switch (c)
    {
      case KEY_LEFT:
          rq.mv_letf();
          break;
      case KEY_RIGHT:
          rq.mv_right();
          break;
      default:
          break;
    }
    
    usleep(50000);
  }

  stopProgramX();
}
