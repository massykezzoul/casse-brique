/*
    Class Brick et définition de l'enumeration Forme (à completer)
    Kezzou Massili : massili.kezzoul@etu.umontpellier.fr
*/
#ifndef BRICK_H
#define BRICK_H

#include "window.h"
#include "player.h"

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
    int width;
    int height;
    Color c;

public:
    /* Constructeur par défault */
    Brick();
    /* Constructeur parametré*/
    Brick(Forme,int resistance,int point,int x,int y,int w,int h,Color = WRED);
    
    Brick(const Brick&);
    /* Destructeur */
    ~Brick();

    /* Operateur d'affectation*/
    Brick& operator=(const Brick&);

    /* Les getteurs */
    Forme get_forme() const;
    int get_resistance() const;
    int get_point() const;

    int get_posX() const;
    int get_posY() const;
    int get_width() const;
    int get_height() const;

    /*  Les setteurs */
    void set_forme(Forme);
    void set_resistance(int);
    void set_point(int);

    /* Pour incrementé la valeur de resistance */
    /* La valeur par défault du paramétre est -1 */
    void increment_resistance(int = -1);

    void clear(const Window*) const;
    void print(const Window*) const;
};

/* ------------------- LA CLASSE TAB_BRICK --------------------- */

class Tab_brick {
private:
    Brick* tab;
    /* Nombre de Brique dans le tableau */
    int size;
    /* Espace mémoire alloué*/
    int alloc;

    static Player* player;
public:
    Tab_brick();
    
    ~Tab_brick();

    /* Ajoute une brique au tableau */
    void add(Forme,int resistance,int point,int x,int y,int w,int h,Color c = WRED);
    void del(int i,const Window* w);
    /* Retourn la brique à la position i*/
    Brick* get_brick(int i = 0);
    int get_size();
    void print(const Window*) const;

    static Player* get_player();
    static void set_player(Player*);

};

#endif
