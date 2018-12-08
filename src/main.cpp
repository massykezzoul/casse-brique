#include "window.h"
#include "Body.h"
#include <unistd.h>

int main () {
  startProgramX();
  Body b(0, 0, 1, 40, WRED, ' ', true, true);
  Body b2(0, 0, 20, 1, WRED, ' ', true, true);
  Body b3(0, 20, 1, 40, WRED, ' ', true, true);
  Body b4(40, 0, 20, 1, WRED, ' ', true, true);
  Body c(10, 10, 1, 1, WRED, ' ', true, false);
  c.SetVelocity(-0.5f, -0.3f);
  while (1) {
    usleep(10000);
    Body::AllUpdate();
  }
  //stopProgramX();
}
