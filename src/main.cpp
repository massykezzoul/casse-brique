#include "window.h"
#include "Body.h"
#include <unistd.h>

int main () {
  startProgramX();
  Window* w = new Window(30, 50, 1, 1, '+');
  w->setCouleurBordure(WBLACK);
  w->setCouleurFenetre(BWHITE);
  Body b(5, 5, 1, 40, WRED, ' ', true, true, w);
  Body b2(5, 5, 20, 1, WRED, ' ', true, true, w);
  Body b3(5, 25, 1, 40, WRED, ' ', true, true, w);
  Body b4(45, 5, 20, 1, WRED, ' ', true, true, w);
  Body c(15, 20, 1, 1, WCYAN, ' ', true, false, w);
  c.SetVelocity(-0.5f, -1);
  while (1) {
    w->clear();
    Body::AllUpdate();
    usleep(100000);
  }
  stopProgramX();
}
