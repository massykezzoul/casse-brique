#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <cstdlib>

#include "window.h"
#include "player.h"
#include "ball.h"
#include "raquette.h"
#include "brick.h"
#include "boutton/boutton.h"

#include "sauvgarde.h"

using namespace std;

/* Les methodes privés */
void Sauvgarde::add_terrain(int x,int y,int w,int h){
    if (size < NB_SAUVGARDE ) {
        terrain[size] = Terrain(h,w,x,y);
    }
}
void Sauvgarde::add_player(string nom,int ball,int score,int niveau,int x,int y,int w,int h){
    if (size < NB_SAUVGARDE ) {
        player[size] = Player(nom,ball,score,niveau,x,y,w,h);
    }
}
void Sauvgarde::add_ball(float x,float y,float speed,float angle,Color c,char car){
    if (size < NB_SAUVGARDE ) {
        ball[size] = Ball(x,y,speed,angle,c,car);
    }
}
void Sauvgarde::add_raquette(int x,int y,int w,int h,int vitesse,Color c,char car){
    if (size < NB_SAUVGARDE ) {
        raquette[size] = Raquette(x,y,w,h,vitesse,c,car);
    }
}
void Sauvgarde::add_tab_btick(){
    if (size < NB_SAUVGARDE ) {
        tab_brick[size] = Tab_brick();
    }
}

/* On donne au constructeur le nom (ou le chemin) du fichier où sont stocké les partie */
Sauvgarde::Sauvgarde(string f):size(0){
    int x[10];
    float y[10];
    char c;
    int deb,fin;
    string line("");
    string name("");
    ifstream file(f.c_str(),ios::in);
    if (!file.fail() && file.good()) {
        getline(file,line);
        while (!file.eof() && size < NB_SAUVGARDE) {
            /* Lecture du terrain */
            fin = -1;
            for (int j = 0; j <= 3;++j) {
                deb = fin;
                fin = line.find_first_of(",",deb+1);
                x[j] = atoi(line.substr(deb+1,fin).c_str());
            }
            add_terrain(x[0],x[1],x[2],x[3]);
            /*---------------------------------------*/
            
            /* Lecture Player */
            getline(file,line);
            deb = line.find_first_of(",");
            name = line.substr(0,deb);
            fin = line.find_first_of(",",deb);
            for (int j = 0; j <= 6;++j) {
                deb = fin;
                fin = line.find_first_of(",",deb+1);
                x[j] = atoi(line.substr(deb+1,fin).c_str());
            }
            add_player(name,x[0],x[1],x[2],x[3],x[4],x[5],x[6]);
            /*---------------------------------------*/
            
            /* Lecture Ball */
            getline(file,line);
            fin = -1;
            for (int j = 0; j <= 4;++j) {
                deb = fin;
                fin = line.find_first_of(",",deb+1);
                y[j] = atof(line.substr(deb+1,fin).c_str());
            }

            deb = fin;
            fin = line.find_first_of(",",deb+1);
            x[0] = atoi(line.substr(deb+1,fin).c_str());

            deb = fin;
            fin = line.find_first_of(",",deb+1);
            c = line.substr(deb+1,fin).c_str()[0];

            add_ball(y[0],y[1],y[2],y[3],IntToColor(x[0]),c);
            /*---------------------------------------*/

            /* Lecture Raquette */
            getline(file,line);
            fin = -1;
            for (int j = 0; j <= 5;++j) {
                deb = fin;
                fin = line.find_first_of(",",deb+1);
                x[j] = atoi(line.substr(deb+1,fin).c_str());
            }
            
            deb = fin;
            fin = line.find_first_of(",",deb+1);
            c = line.substr(deb+1,fin).c_str()[0];
            
            add_raquette(x[0],x[1],x[2],x[3],x[4],IntToColor(x[5]),c);
            /*---------------------------------------*/
            /* lecture des brick */
            getline(file,line);
            x[0] = atoi(line.substr(0,line.find_first_of(",")).c_str());
            for(int i = 0 ; i < x[0] ; ++i) {
                getline(file,line);
                fin = -1;
                for (int j = 1; j <= 8;++j) {
                    deb = fin;
                    fin = line.find_first_of(",",deb+1);
                    x[j] = atoi(line.substr(deb+1,fin).c_str());
                }
                tab_brick[size].add(IntToForme(x[1]),x[2],x[3],x[4],x[5],x[6],x[7],IntToColor(x[8]));
            }
            size++;
            getline(file,line);
        }
        file.clear();
        file.close();
    }
}

/* Ecrire dans le fichier */
void Sauvgarde::write(string name){
    ofstream file(name.c_str(),ios::out | ios::trunc);
    Brick* b = NULL;
    if (!file.fail() && file.good()) {
        for (int i = 0; i < size ; ++i) {
            file<<terrain[i].get_posX()<<","<<terrain[i].get_posY()<<","<<terrain[i].get_width()<<","<<terrain[i].get_height()<<","<<endl;
            file<<player[i].get_name()<<","<<player[i].get_ball()<<","<<player[i].get_score()<<","<<player[i].get_niveau()<<","<<player[i].get_window().getX()<<","<<player[i].get_window().getY()<<","<<player[i].get_window().getLargeur()<<","<<player[i].get_window().getHauteur()<<","<<endl;
            file<<ball[i].get_posX()<<","<<ball[i].get_posY()<<","<<ball[i].get_speed()<<","<<ball[i].get_angle()<<","<<ball[i].get_color()<<","<<ball[i].get_char()<<","<<endl;
            file<<raquette[i].get_posX()<<","<<raquette[i].get_posY()<<","<<raquette[i].get_width()<<","<<raquette[i].get_height()<<","<<raquette[i].get_speed()<<","<<raquette[i].get_color()<<","<<raquette[i].get_char()<<","<<endl;
            file<<tab_brick[i].get_size()<<","<<endl;
            for (int j=0 ; j < tab_brick[i].get_size() ; ++j) {
                b = tab_brick[i].get_brick(j);
                file<<b->get_forme()<<","<<b->get_resistance()<<","<<b->get_point()<<","<<b->get_posX()<<","<<b->get_posY()<<","<<b->get_width()<<","<<b->get_height()<<","<<b->get_color()<<","<<endl;
            }
        }
        file.clear();
        file.close();
    }
}

/* Supprime la sauvgarde numéro i */
void Sauvgarde::del(int i){
    if (i < size) {
        --size;
        for (int j = i ; j < size;j++) {
            terrain[j] = terrain[j+1];
            player[j] = player[j+1];
            ball[j] = ball[j+1];
            raquette[j] = raquette[j+1];
            tab_brick[j] = tab_brick[j+1];
        }
    }
}

/* sauvgarde dans le fichier donnée en paramètre (si la sauvgarde existe déja elle sera ecrasé) */
void Sauvgarde::sauvgarder(const Terrain& w,const Player& p,const Ball& b,const Raquette& r,const Tab_brick& t,int numero_sauvgarde){
    /* On suprimme l'element 'numero_sauvgarde' si il n'y a plus d'espace */
    if (size >= NB_SAUVGARDE)
        del(numero_sauvgarde);

    terrain[size] = w;
    player[size] = p;
    ball[size] = b;
    raquette[size] = r;
    tab_brick[size] = t;
    size++;
}

/* retourne les infomarion pour chargé la partie dont le numéro est donnée en paramètre */
void Sauvgarde::charger(int numero_sauvgarde,Terrain& w,Player& p,Ball& b,Raquette& r,Tab_brick& t) const{
    if (numero_sauvgarde < size) {
        w = terrain[numero_sauvgarde];
        p = player[numero_sauvgarde];
        b = ball[numero_sauvgarde];
        r = raquette[numero_sauvgarde];
        t = tab_brick[numero_sauvgarde];
    }
}

/* Affiche les partie sauvgardé */
void Sauvgarde::print(/*const Window* w*/) const{
    /*
    int x = (int)(0.15*(w->getX()+w->getLargeur()));
    int y = (int)(0.15*(w->getY()+w->getHauteur()));
    */
    int x = 10;
    int y = 10;
    Color c = BWHITE;
    stringstream ss("");
    
    if (size == 0 ){
        /* Aucune partie sauvgarder */
        Window win(5,35,x,y,' ');
        string separateur(win.getLargeur(),'-');

        win.setCouleurBordure(c);
        win.setCouleurFenetre(WBLACK);
        /* Affichage du msg */
        win.print(0,0,separateur);
        win.print(0,1,"Aucune Partie Sauvgardé");
        win.print(0,2,separateur);
        /* Le boutton OK */
        Boutton ok(" [  OK  ] ",0,WBLACK ,c ,true);
        ok.print(&win,(int)(0.30*(win.getX()+win.getLargeur())),3);

        win.print(0,4,separateur);

        int car = 0;
        while (car != '\n' && car != 'q' && car != 'Q' && car != ' ' ) {
            car = 0;
            car = getch();
            usleep(50000);
        }    
        win.clear();
    } else {
        Window win(size+5,35,x,y,' ');
        string separateur(win.getLargeur(),'-');

        win.setCouleurBordure(c);
        win.setCouleurFenetre(WBLACK);
        /* Affichage du msg */
        ss << "nb : " << size;
        win.print(0,0,separateur);
        win.print(0,1,ss.str());
        win.print(0,2,separateur);
        ss.str("");
        /* Affichages des scores */
        for(int i = 0;i<size;++i ){
            ss << i+1<<"- " <<player[i].get_name() << " : " << player[i].get_score() << " Points" << endl;
            win.print(1,i+3,ss.str());
            ss.str("");
        }
        win.print(0,NB_SAUVGARDE+3,separateur);
        /* Le boutton OK */
        Boutton ok(" [  OK  ] ",0,WBLACK ,c ,true);
        ok.print(&win,(int)(0.30*(win.getX()+win.getLargeur())),NB_SAUVGARDE+4);

        win.print(0,NB_SAUVGARDE+5,separateur);

        int car = 0;
        while (car != '\n' && car != 'q' && car != 'Q' && car != ' ' ) {
            car = 0;
            car = getch();
            usleep(50000);
        }
        win.clear();
    }
}