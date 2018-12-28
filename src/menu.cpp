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
#include "score.h"
#include "sauvgarde.h"

using namespace std;

#define KEY_SPACE ' '
#define KEY_ETR '\n'
#define FICHIER_SAUVGARDE ".savedGames"

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
            c = getch(); 
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
                    c = ERR;
                    usleep(50000);
                    break;
            }

        } while ( c == ERR );
    }   
    win.clear();
    return sel;
}

void jouer(){
    //Initialisation
    Window terrain(25, 50, 0, 0);
    terrain.setCouleurBordure(BWHITE);
    terrain.setCouleurFenetre(WBLACK);
    /* Les arguments c'est pour placé les stats à droite du Terrain */ 
    Player* p = new Player("Massy",5,0,2,terrain.getLargeur()+terrain.getX()+2,terrain.getY(),23,terrain.getHauteur());
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
    Raquette rq(10,20,15,1,3,terrain.getCouleurFenetre(),'-');
    
    Ball ball(rq,terrain.getCouleurBordure());

    float speed = 1.0;
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
            rq.mv_right(terrain.getLargeur() + terrain.getX());
            rq.print(&terrain);
            if (ball.get_speed() == 0) {                
                ball.clear(&terrain);
                ball.set_pos(rq);
                ball.print(&terrain);
            }
            break;
        case KEY_SPACE:
            if (ball.get_speed() == 0) {
                ball.set_speed(speed);
                ball.set_angle(-45);
            }
        default:
            break;
        }
        if (ball.get_posY()> rq.get_posY()+rq.get_height()) {
            // Kill the ball
            // Affichage de ball en moin 
            terrain.setCouleurBordure(BRED);
            ball.clear(&terrain);
            p->increment_ball();
            if (p->get_ball() == 0) {
                //affiche msg fin de partie PERDU
                c= 'q';
            } else {
                ball.set_pos(rq);
                ball.set_speed(0);
                ball.print(&terrain);
                p->print();
            }
            usleep(50000);
            terrain.setCouleurBordure(BWHITE);
        }

        if (tab.get_brick() == NULL) {
            //Fin de partie toute les brick on été detruite GAGNÉ
            // Passer au niveau suivant
            c = 'q';
        }

        if (ball.get_speed() != 0) {    
            ball.update(tab,rq,&terrain);
            p->print();
        }
        usleep(50000);
    }
    /* Sauvgarde du score */
    Score s("hightScore.txt");
    s.add(*p);
    s.print(&terrain);
    s.write("hightScore.txt");

    /* Destruction de tout les objets */
    delete p;
    tab.~Tab_brick();
    ball.~Ball();
    rq.~Raquette();
    terrain.clear();

}

void charger() {
    Window win(25,50,0,0,' ');
    win.setCouleurBordure(BWHITE);
    win.setCouleurFenetre(WBLACK);
    Sauvgarde save(FICHIER_SAUVGARDE);
    save.print(&win);
}

void score(){
    Window win(25,50,0,0,' ');
    win.setCouleurBordure(BWHITE);
    win.setCouleurFenetre(WBLACK);
    Score s("hightScore.txt");
    s.print(&win);
    s.~Score();
    win.clear();
}
 
void option(){

}
