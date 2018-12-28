#ifndef RAQUETTE_H
#define RAQUETTE_H

#include "window.h"

class Raquette {
private:
    int posX;
    int posY;
    int width;
    int height;
    int vitesse;
    Color c;
    char car;
public:
    Raquette();
    Raquette(int posX,int posY,int width,int height,int vitesse,Color c = WGREEN,char car = '-');
    ~Raquette();

    /* Donne la position du coin supérieur gauche de la raquette */
    int get_posX()const;
    int get_posY()const;
    
    /* Donne la largeur et la hauteur de la raquette */
    int get_width()const;
    int get_height()const;

    int get_speed()const;
    Color get_color()const;
    char get_char()const;

    /* Changer la position du coin supérieur gauche de la raquette */
    void set_posX(int);
    void set_posY(int);
    void set_pos(int,int);
    
    /* Changer la largeur et la hauteur de la raquette */
    void set_width(int);
    void set_height(int);

    /* Change la position de X (X--) ce qui la fait bouger vers la gauche */
    void mv_left(int limite = 0);
    /* Change la position de X (X++) ce qui la fait bouger vers la Droite */
    void mv_right(int limite);

    void clear(const Window*)const ;
    void print(const Window*)const ;

};

#endif