/*
    Declaration de la classe Ball
    Massili Kezzoul
*/
#ifndef BALL_H
#define BALL_H

#include "brick.h"
#include "raquette.h"
#include "window.h"

class Ball {
private:
/* Vitesse et angle*/
    float posX;
    float posY;
    float speed;
    float angle;
    float velX;
    float velY;
    Color color;
    char c;
public:
/* Constructeur */
    Ball();
    Ball(const Raquette&,Color = WCYAN,char = 'O');
    Ball(float posX,float posY,float spd,float angl,Color = WCYAN, char = 'O');
    Ball(const Ball&);
    Ball& operator=(const Ball&);

    void apply_velocity();
/* Getteurs */
    float get_posX() const;
    float get_posY() const;
    float get_velX() const;
    float get_velY() const;
    float get_speed() const;
    float get_angle() const;
    Color get_color() const;
    char get_char() const;


/* Setteurs*/
    void set_posX(float);
    void set_posY(float);
    void set_pos(float,float);
    void set_pos(const Raquette&);
    void set_velX(float);
    void set_velY(float);
    void set_vel(float,float);
    void set_vel(int normal);
    void set_speed(float);
    void set_angle(float);

    void print(const Window*) const;
    void clear(const Window*) const;

    //
    void update(Tab_brick&,const Raquette&,Window*);
/* Gestion des colisions */

    /*
        Types de colision : 
                1
             _______
            |       |
       4->  |       |  <-2
            |_______|
               
                3
            0 : pas de colision
    
    */
   void allCollision(Tab_brick&,const Raquette&,Window*);
   /* Prend un tableau de brick en parametre */
   int collideBrick(Tab_brick&,const Window*) const;
   int collideBrick(Brick&) const;
   int collideRaquette(const Raquette&) const;
   int collideBord(const Window*) const;

};

/* ------------------------ CLASSE TAB_BALL ------------------------------*/

class Tab_ball {
    private:
    Ball* tab;
    /* Nombre de Brique dans le tableau */
    int size;
    /* Espace mémoire alloué*/
    int alloc;

    static Player* player;
public:
    Tab_ball();
    
    ~Tab_ball();

    /* Ajoute une brique au tableau */
    void add(float posX,float posY,float spd,float angl,Color = WCYAN, char = '@');
    void add(const Raquette&,Color = WCYAN, char = 'O');
    void del(int i,const Window* w);
    /* Retourn la brique à la position i*/
    Ball* get_ball(int i = 0);
    int get_size();
    void print(const Window*) const;

    static Player* get_player();
    static void set_player(Player*);

};
#endif
