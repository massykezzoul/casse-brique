/*
    Class Brick et définition de l'enumeration Forme (à completer)
    Kezzou Massili : massili.kezzoul@etu.umontpellier.fr
*/
#ifndef BRICK_H
#define BRICK_H

#include "player.h"
#include "Body.h"

enum Forme
{
    CARRE,
    TRIANGLE,
    CREUSE,
    RONDE,
    NB_FORME
};

class Body;

/* ------------ LA CLASSE BRICK ----------------- */

class Brick {
private:
    /* data */
    /* La forme de la brique */
    Forme forme;
    /* Le nombre de coup qu'il faut pour la casser */
    int resistance;
    /* Le nombre de point qu'elle fait gagner */
    int point;
    int x;
    int y;
    Body body;
    static Player* player;

public:
    /* Constructeur par défault */
    Brick();
    /* Constructeur parametré*/
    Brick(Forme,int,int,int,int);
    /* Destructeur */
    ~Brick();

    /* Les getteurs */
    Forme get_forme() const;
    int get_resistance() const;
    int get_point() const;

    /*  Les setteurs */
    void set_forme(Forme);
    void set_resistance(int);
    void set_point(int);
    static void set_player(Player* p);
    static Player* get_player();

    /* Pour incrementé la valeur de resistance */
    /* La valeur par défault du paramétre est -1 */
    void increment_resistance(int = -1);

    void on_colision();

};



#endif
