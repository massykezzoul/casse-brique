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
    int c=0;
    while (sel == -1) {
        tab.print(&win);
        c=0;
        do {
            c=getch();
        } while ( c == 0 );

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
    Player* p = new Player("Phase de Dev",5,0,2,terrain.getLargeur()+terrain.getX()+2,terrain.getY(),25,terrain.getHauteur());
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
    
    Tab_ball tab_ball;
    tab_ball.set_player(p);
    for (int i = 0 ; i < p->get_ball() ;++i) 
        tab_ball.add(rq,WBLACK);
    Ball ball(*tab_ball.get_ball());

    tab.print(&terrain);
    ball.print(&terrain);
    rq.print(&terrain);
    p->print();

    //Jeu
    int c = 0;
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
        if (ball.get_posY()> rq.get_posY()+rq.get_height()) {
            // Kill the ball
            // Affichage de ball en moin 
            ball.clear(&terrain);
            p->increment_ball();
            tab_ball.del(0,&terrain);
            if (tab_ball.get_ball() == NULL) {
                //affiche msg fin de partie
                // Stockage des point tout ça tout ça
                c= 'q';
            } else {
                ball = *tab_ball.get_ball();
                ball.set_pos(rq);
                ball.print(&terrain);
                p->print();
            }
        }
        if (tab.get_brick() == NULL) {
            //Fin de partie toute les brick on été detruite
            // Stockage des point tout ça tout ça
            c = 'q';
        }

        if (ball.get_speed() != 0) {    
            ball.update(tab,rq,&terrain);
            p->print();
        }
        usleep(50000);
    }
    /* Destruction de tout les objets */
    delete p;
    tab.~Tab_brick();
    tab_ball.~Tab_ball();
    rq.~Raquette();
    terrain.clear();

}

void score(){

}
 
void option(){

}
