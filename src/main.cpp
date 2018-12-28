#include "window.h"
#include "player.h"
#include "brick.h"
#include "ball.h"
#include "raquette.h"
#include "menu.h"
#include <unistd.h>


int main () {
  startProgramX();
  
  int i = menu();
  while (i != 5) {
    if (i==1) jouer();
    else if (i == 2) charger();
    else if (i == 3) option();
    else if (i == 4) score();
    else if (i == 5) break;
    else exit(1);

    i = menu();
  }

  stopProgramX();
}
