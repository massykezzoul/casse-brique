#ifndef RAQUETTE_H
#define RAQUETTE_H

#include "Body.h"

class Raquette {
private:
    Body body;
public:
    Raquette();
    Raquette(int posX,int posY,int width,int height, Color c = WCYAN);
    ~Raquette();

    /* Donne la position du coin supérieur gauche de la raquette */
    float get_posX();
    float get_posY();
    
    /* Donne la largeur et la hauteur de la raquette */
    int get_width();
    int get_height();

    /* Changer la position du coin supérieur gauche de la raquette */
    void set_posX(float);
    void set_posY(float);
    void set_pos(float,float);
    
    /* Changer la largeur et la hauteur de la raquette */
    void set_width(int);
    void set_height(int);

    /* Change la position de X (X--) ce qui la fait bouger vers la gauche */
    void mv_left();
    /* Change la position de X (X++) ce qui la fait bouger vers la Droite */
    void mv_right();
};

#endif