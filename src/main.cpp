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
  while (i != 4) {
    if (i==1) jouer();
    else if (i == 2) option();
    else if (i == 3) score();
    else exit(1);

    i = menu();
  }

  stopProgramX();
}
