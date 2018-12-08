#include "window.h"
#include "Body.h"
#include <unistd.h>

int main () {
  startProgramX();
  Body b(0, 0, 1, 40, WRED, ' ', true, true, false);
  Body b2(0, 0, 20, 1, WRED, ' ', true, true, false);
  Body b3(0, 20, 1, 40, WRED, ' ', true, true, false);
  Body b4(40, 0, 20, 1, WRED, ' ', true, true, false);
  Body c(10, 10, 1, 1, WBLACK, ' ', true, false, true);
  c.SetVelocity(-0.5f, -1);
  while (1) {
    usleep(10000);
    Body::AllUpdate();
  }
  //stopProgramX();
}
