/* 
    Declaration de la classe Ball 
    Massili Kezzoul
*/
#ifndef BALL_H
#define BALL_H

#include "Body.h"
//#include "../window.h"

class Ball {
private:
/* Position */
    float posX;
    float posY;
/* Velocité*/
    float velX;
    float velY;
/* Peut être pour modifié la taille de la balle (actuellement par défault 1 et 1) */
/* 
    int width;
    int height;
*/
    Body body;
public:
/* Constructeur */
    Ball();
    Ball(int posX,int posY,float velX,float velY,Color c = WCYAN);
    ~Ball();
/* Getteurs */
    float get_posX() const;
    float get_posY() const;
    float get_velX() const;
    float get_velY() const;

/* Setteurs*/
    void set_posX(float);
    void set_posY(float);
    void set_pos(float,float);
    void set_velX(float);
    void set_velY(float);
    void set_vel(float,float);

/* Mise à jour de sa position */
    void update();
};

#endif