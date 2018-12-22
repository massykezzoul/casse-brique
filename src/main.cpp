#include "window.h"
#include "Body.h"
#include "player.h"
#include "brick.h"
#include "Terrain.h"
#include "ball.h"
#include "raquette.h"
#include <unistd.h>

#define KEY_SPACE ' '

int main () {
  startProgramX();
  //Initialisation
  Terrain t(0, 0, 50, 25);
  /* Les arguments c'est pour placé les stats à droite du Terrain */ 
  Player* p = new Player(t.get_width()+t.get_posX()+1,t.get_posY(),25,t.get_height());
  Brick::set_player(p);
  //Niveau
  Brick b1(CARRE, 1, 10, 25, 5);
  Brick b2(CARRE, 1, 10, 5, 5);
  Brick b3(CARRE, 1, 10, 9, 5);
  Brick b4(CARRE, 1, 10, 13, 5);
  Brick b5(CARRE, 1, 10, 17, 5);
  Brick b6(CARRE, 1, 10, 21, 5);
  //Raquette
  Raquette rq(10,20,1,20,WGREEN);
  
  //Balle  (Les arguments compliqué c'est juste pour positionné la Balle au dessu de la raquette en debut de partie)
  Ball ball((2*rq.get_posX()+rq.get_width())/2 , rq.get_posY()-1 , 0, 0,WCYAN);
  //Jeu
  int c=0;

  while (c != 'q' && c != 'Q')  {
    t.Update();
    p->print();
    
    c=0;
    c=getch();
    switch (c)
    {
      case KEY_LEFT:
          rq.mv_left();
          if (ball.get_speed() == 0) ball.mv_left();
          break;
      case KEY_RIGHT:
          rq.mv_right();
          if (ball.get_speed() == 0) ball.mv_right();
          break;
      case KEY_SPACE:
          if (ball.get_speed() == 0) {
            ball.set_speed(1.0);
            ball.set_angle(45);
          }
      default:
          break;
    }
    
    usleep(50000);
  }

  stopProgramX();
}
