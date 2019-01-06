#include "window.h"
#include "player.h"
#include "brick.h"
#include "ball.h"
#include "raquette.h"
#include "menu.h"
#include  "option/option.h"
#include <unistd.h>


int main (int argc,const char* argv[]) {
  std::string config_file = "config/config.cfg";

  Option_tab mes_option;
  if (argc > 1) {
    mes_option.gere_parametre(argc,argv,config_file);
  }
  

  startProgramX();
  
  int i = menu();
  int save = -1;
  while (i != 5) {
    if (i==1) jouer(config_file);
    else if (i == 2) {
      save = charger();
      if (save != -1) jouer(config_file,save);
    }
    else if (i == 3) option();
    else if (i == 4) score();
    else if (i == 5) break;
    else exit(1);

    i = menu();
  }

  stopProgramX();
}
