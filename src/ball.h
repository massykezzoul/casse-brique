/*
    Declaration de la classe Ball
    Massili Kezzoul
*/
#ifndef BALL_H
#define BALL_H

#include "Body.h"

class Ball {
private:
/* Vitesse et angle*/
    float speed;
    float angle;
    
    Body body;
public:
/* Constructeur */
    Ball();
    Ball(int posX,int posY,float spd,float angl,Color c = WCYAN);
    ~Ball();

    void apply_velocity();
/* Getteurs */
    float get_posX() const;
    float get_posY() const;
    float get_velX() const;
    float get_velY() const;
    float get_speed() const;
    float get_angle() const;

/* Setteurs*/
    void set_posX(float);
    void set_posY(float);
    void set_pos(float,float);
    void set_velX(float);
    void set_velY(float);
    void set_vel(float,float);
    void set_vel(int normal);
    void set_speed(float);
    void set_angle(float);

    void mv_left();
    void mv_right();
};

#endif
