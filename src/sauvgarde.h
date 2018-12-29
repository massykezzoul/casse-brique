#ifndef SAUVGARDE_H
#define SAUVGARDE_H

#include "window.h"
#include "player.h"
#include "ball.h"
#include "raquette.h"
#include "brick.h"


#define NB_SAUVGARDE 6

class Sauvgarde {
private:
    /* Nombre de partie sauvgardé */
    int size;
    
    Window terrain[NB_SAUVGARDE];
    Player player[NB_SAUVGARDE];
    Ball ball[NB_SAUVGARDE];
    Raquette raquette[NB_SAUVGARDE];
    Tab_brick tab_brick[NB_SAUVGARDE];

    void add_terrain(int x,int y,int w,int h);
    void add_player(std::string,int ball,int score,int niveau,int x,int y,int w,int h);
    void add_ball(float x,float y,float speed,float angle,Color c,char car);
    void add_raquette(int x,int y,int w,int h,int vitesse,Color c,char car);
    void add_tab_btick();

public:
    /* On donne au constructeur le nom (ou le chemin) du fichier où sont stocké les partie */
    Sauvgarde(std::string);

    /* Ecrire dans le fichier */
    void write(std::string);

    /* Supprime la sauvgarde numéro i*/
    void del(int i);

    /* sauvgarde dans le fichier donnée en paramètre (si la sauvgarde existe déja elle sera ecrasé) */
    void sauvgarder(int numero_sauvgarde,const Window&,const Player&,const Ball&,const Raquette&,const Tab_brick&);

    /* retourne les infomarion pour chargé la partie dont le numéro est donnée en paramètre */
    void charger(int numero_sauvgarde,Window&,Player&,Ball&,Raquette&,Tab_brick&) const;

    /* Affiche les partie sauvgardé */
    void print(const Window*) const;
};


#endif