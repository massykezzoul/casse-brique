#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unistd.h> // usleep()
#include <cstdlib> // srand() , rand()
#include <ctime> // time()
#include "window.h"

#include "player.h"
#include "brick.h"
#include "ball.h"
#include "raquette.h"
#include "Terrain.h"
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

    Tab_boutton tab;

    int x = (win.getX() + win.getLargeur()) / 2 - 3;
    int y = win.getY() + 8;

    tab.add("Jouer",x,y,fond,on_focus,true);
    tab.add("Charger",x,y+1,fond,on_focus);
    tab.add("Options",x,y+2,fond,on_focus);
    tab.add("Scores",x,y+3,fond,on_focus);
    tab.add("Quitter",x,y+4,fond,on_focus);

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

void jouer(int i){
    //Initialisation
    Terrain terrain(0,0, 50, 25);
    Tab_brick tab;
    Player* p;
    if (i == -1) {
        /* Les arguments c'est pour placé les stats à droite du Terrain */ 
        p = new Player("Massy",10,0,3,terrain.get_width()+terrain.get_posX()+2,terrain.get_posY(),23,terrain.get_height());
        //Niveau
        tab.add(CARRE, 2, 20, 2, 1,6,2,WGREEN);
        tab.add(CARRE, 2, 20, 15, 1,6,2,WGREEN);
        tab.add(CARRE, 2, 20, 30, 1,6,2,WGREEN);
        tab.add(CARRE, 2, 20, 43, 1,6,2,WGREEN);

        tab.add(CARRE, 1, 10, 2, 5,6,2);
        tab.add(CARRE, 1, 10, 15, 5,6,2);
        tab.add(CARRE, 1, 10, 30, 5,6,2);
        tab.add(CARRE, 1, 10, 43, 5,6,2);

    } else {
        /* Charger une partie depuis la sauvgarde */
        Tab_save saves(FICHIER_SAUVGARDE);
        Save save = saves.get_save(i);
        p = new Player(save.get_name(),save.get_vie(),save.get_score(),save.get_niveau(),terrain.get_width()+terrain.get_posX()+2,terrain.get_posY(),23,terrain.get_height());
        tab = save.get_brick();
    }
    
    tab.set_player(p);

    //Raquette
    Raquette rq(10,20,15,1,3,WBLACK,'-');
    
    Ball ball(rq,WBLACK);
    /* angle random */
    srand(time(NULL));
    float angle = -45;
    float speed = 1.0;
    tab.print(terrain.GetWindow());
    ball.print(terrain.GetWindow());
    rq.print(terrain.GetWindow());
    p->print();

    //Jeu
    int c = 0;
    while (c != 'q' && c != 'Q')  {
        c=0;
        c=getch();
        switch (c)
        {
        case KEY_LEFT:
            rq.clear(terrain.GetWindow());
            rq.mv_left(0);
            rq.print(terrain.GetWindow());
            if (ball.get_speed() == 0) {
                ball.clear(terrain.GetWindow());
                ball.set_pos(rq);
                ball.print(terrain.GetWindow());
            }
            break;
        case KEY_RIGHT:
            rq.clear(terrain.GetWindow());
            rq.mv_right(terrain.get_width() + terrain.get_posX());
            rq.print(terrain.GetWindow());
            if (ball.get_speed() == 0) {                
                ball.clear(terrain.GetWindow());
                ball.set_pos(rq);
                ball.print(terrain.GetWindow());
            }
            break;
        case KEY_SPACE:
            if (ball.get_speed() == 0) {
                ball.set_speed(speed);
                /* random angle */
                do{
                    angle = rand() % 180;
                } while ((angle > 155 || (angle < 110 && angle > 70 ) || (angle < 25)) );
                angle = -angle;
                ball.set_angle(angle);
            }
        default:
            break;
        }
        if (ball.get_posY()> rq.get_posY()+rq.get_height()) {
            // Kill the ball
            // Affichage de ball en moin 
            terrain.GetWindow()->setCouleurBordure(BRED);
            ball.clear(terrain.GetWindow());
            p->increment_ball();
            if (p->get_ball() == 0) {
                //affiche msg fin de partie PERDU
                c= 'q';
            } else {
                ball.set_pos(rq);
                ball.set_speed(0);
                ball.print(terrain.GetWindow());
                p->print();
            }
            usleep(30000);
            terrain.GetWindow()->setCouleurBordure(BWHITE);
        }

        if (tab.get_brick() == NULL) {
            //Fin de partie toute les brick on été detruite GAGNÉ
            // Passer au niveau suivant
            c = 'q';
        }

        if (ball.get_speed() != 0) {    
            ball.update(tab,rq,terrain.GetWindow());
            p->print();
        }
        usleep(30000);
    }
    if (p->get_ball() != 0 && tab.get_brick() != NULL) {
        // Partie non términé proposé de sauvgarder
        Window boite(3,25,(int)(0.25*(terrain.get_posX()+terrain.get_width())),(int)(0.15*(terrain.get_posY()+terrain.get_height())),' ');
        Tab_boutton boutton_tab;
        boutton_tab.add("[ SAVE ]",2,1,WBLACK,BWHITE,true);
        boutton_tab.add("[ QUIT ]",14,1,WBLACK,BWHITE,false);

        int car = 0;
        int sel = -1;
        boutton_tab.print(&boite);
        while (car != '\n') {
            do {
                car = getch(); 
                switch (car)
                {
                    case KEY_RIGHT:
                        boutton_tab.down();
                        boutton_tab.print(&boite);
                        break;
                    case KEY_LEFT:
                        boutton_tab.up();
                        boutton_tab.print(&boite);
                        break;
                    case '\n':
                        sel = boutton_tab.get_selected();
                        break;
                    default:
                        car = ERR;
                        usleep(50000);
                        break;
                }
            } while (car == ERR);
        }
        if (sel == 1) {
            Tab_save save(FICHIER_SAUVGARDE);
            save.add(p->get_name(),p->get_ball(),p->get_score(),p->get_niveau(),tab);
            save.write(FICHIER_SAUVGARDE);
            save.print(terrain.GetWindow());
        }
    }
    else {
        // Partie términé pas de sauvgarde possible
        /* Sauvgarde du score */
        Score s("hightScore.txt");
        s.add(*p);
        s.print(terrain.GetWindow());
        s.write("hightScore.txt");
    }
    /* Destruction de tout les objets */
    delete p;
    terrain.clear();
}

int charger() {
    Window win(25,50,0,0,' ');
    win.setCouleurBordure(BWHITE);
    win.setCouleurFenetre(WBLACK);
    Tab_save save(FICHIER_SAUVGARDE);
    int selection = save.print(&win);
    if (selection == -1 )
        return -1;
    else {
        /* Proposé de charger ou supprimer */
        Window boite(3,27,(int)(0.25*(win.getX()+win.getLargeur())),(int)(0.15*(win.getY()+win.getHauteur())),' ');
        Tab_boutton tab;
        tab.add("[ CHARGER ]",2,1,WBLACK,BWHITE,true);
        tab.add("[ SUPPRIMER ]",14,1,WBLACK,BWHITE,false);

        int car = 0;
        int sel = -1;
        tab.print(&boite);
        while (car != '\n') {
            do {
                car = getch(); 
                switch (car)
                {
                    case KEY_RIGHT:
                        tab.down();
                        tab.print(&boite);
                        break;
                    case KEY_LEFT:
                        tab.up();
                        tab.print(&boite);
                        break;
                    case '\n':
                        sel = tab.get_selected();
                        break;
                    default:
                        car = ERR;
                        usleep(50000);
                        break;
                }
            } while (car == ERR);
        }
        if  (sel == 1) return selection; // Charger
        else if (sel == 2 ) {
            // Supprimer
            save.del(selection);
            save.write(FICHIER_SAUVGARDE);
            return -1;
        } else return -1;
    }
}

void score(){
    Window win(25,50,0,0,' ');
    win.setCouleurBordure(BWHITE);
    win.setCouleurFenetre(WBLACK);
    Score s("hightScore.txt");
    s.print(&win);
    win.clear();
}
 
void option(){

}
