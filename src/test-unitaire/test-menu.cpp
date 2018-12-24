#include <iostream>
#include <fstream>
#include "menu.h"
#include "window.h"

using namespace std;

// Compilation 
//      g++ -lncurses test-menu.cpp ../menu.cpp ../window.cpp -o menu

int main(int argc, char const *argv[])
{
    startProgramX();

    int i;
    do {
        i = menu();
        exit(1);
        /*switch ( i )
        {
            case 0:
                cerr << "ERREUR d'execution du programme." << endl;
                exit(1);
                break;
            case 1:
                jouer();
                break;
            case 2:
                option();
                break;
            case 3:
                score();
                break;
            case 4:
                break;
            default:
                cerr << "ERREUR d'execution du programme." << endl;
                exit(1);
                break;
        }
        */
       i=4;
    } while (i != 4);
    
    stopProgramX();
    return 0;
}
