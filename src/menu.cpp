#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include "window.h"

#include "player.h"
#include "brick.h"
#include "ball.h"
#include "raquette.h"
#include "menu.h"
#include "boutton/boutton.h"

using namespace std;

#define KEY_SPACE ' '
#define KEY_ETR '\n'

int menu(Color fond,Color bordure){
    Window win(25,50,0,0,' ');
    win.setCouleurBordure(bordure);
    win.setCouleurFenetre(fond);

    Color on_focus = BWHITE;

    Tab_boutton tab(fond,on_focus);
    int sel = -1;
    int c;
    while (sel == -1) {
        tab.print(&win);
        c=0;
        c=getch();
        switch (c)
        {
            case KEY_DOWN:
                tab.down();
                break;
            case KEY_UP:
                tab.up();
                break;
            case KEY_ETR:
                sel = tab.get_selected();
                break;
            default:
                break;
        }   
    }   
    win.clear();
    return sel;
}

void jouer(){
    //Initialisation
    Window terrain(25, 50, 0, 0);
    /* Les arguments c'est pour placé les stats à droite du Terrain */ 
    Player* p = new Player("Phase de test",5,0,2,terrain.getLargeur()+terrain.getX()+2,terrain.getY(),25,terrain.getHauteur());
    //Niveau
    Tab_brick tab;

    
    tab.set_player(p);

    tab.add(CARRE, 1, 10, 5, 5,4,2);
    //tab.add(CARRE, 1, 10, 9, 5,4,2);
    tab.add(CARRE, 1, 10, 13, 5,4,2);
    //tab.add(CARRE, 1, 10, 17, 5,4,2);
    tab.add(CARRE, 1, 10, 21, 5,4,2);
    //tab.add(CARRE, 1, 10, 25, 5,4,2);
    tab.add(CARRE, 1, 10, 29, 5,4,2);
    //tab.add(CARRE, 1, 10, 33, 5,4,2);

    //Raquette
    Raquette rq(10,20,15,1,3);
    
    //Balle  (Les arguments compliqué c'est juste pour positionné la Balle au dessu de la raquette en debut de partie)
    Ball ball((2*rq.get_posX()+rq.get_width())/2 , rq.get_posY()-1 , 0, 0,WBLACK,'O');
    //Ball ball(10 , 15 , 1, 45,WCYAN);
    //Jeu
    int c;

    stringstream s;
    s.str("");

    tab.print(&terrain);
    ball.print(&terrain);
    rq.print(&terrain);
    p->print();

    while (c != 'q' && c != 'Q')  {
        c=0;
        c=getch();
        switch (c)
        {
        case KEY_LEFT:
            rq.clear(&terrain);
            rq.mv_left(0);
            rq.print(&terrain);
            if (ball.get_speed() == 0) {
                ball.clear(&terrain);
                ball.set_pos(rq);
                ball.print(&terrain);
            }
            break;
        case KEY_RIGHT:
            rq.clear(&terrain);
            rq.mv_right(50); // Le 50 c'est la largeur du terrain + posX
            rq.print(&terrain);
            if (ball.get_speed() == 0) {                
                ball.clear(&terrain);
                ball.set_pos(rq);
                ball.print(&terrain);
            }
            break;
        case KEY_SPACE:
            if (ball.get_speed() == 0) {
                ball.set_speed(1.0);
                ball.set_angle(-45);
            }
        default:
            break;
        }
        if (ball.get_speed() != 0) {    
            ball.update(tab,rq,&terrain);
            p->print();
        }
        usleep(50000);
    }
  
}

void score(){

}
 
void option(){

}
