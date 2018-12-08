#include "window.h"
#include "Body.h"
#include <unistd.h>

int main () {
  startProgramX();
  Body b(1, 1, 5, 5, WRED, ' ', true, true);
  Body b2(10, 10, 5, 5, WRED, ' ', true, true);
  Body c(20, 20, 1, 1, WBLACK, ' ', true, false);
  c.SetVelocity(1, 1);
  while (1) {
    sleep(1);
    c.Update();
  }
  stopProgramX();
}
