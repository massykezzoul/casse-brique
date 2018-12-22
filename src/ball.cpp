#include "Body.h"
#include "ball.h"

#include <math.h>

#define PI 3.14159265

using namespace std;

/* Constructeur */

Ball::Ball():speed(0.1),angle(45),body(10, 10, 1, 1, WCYAN, true, false) {
  apply_velocity();
}

// on donne la vitesse et l'angle de la balle au constructeur !
Ball::Ball(int posX,int posY,float spd,float angl,Color c)
    :speed(spd),angle(angl),body(posX, posY, 1, 1, c, true, false){
  apply_velocity();
}

Ball::~Ball(){

}

//Grace a l'angle on récupere la velocité x et y avec cos et sin
//on multiplie vx et vy par speed pour avoir la vitesse de la balle.
void Ball::apply_velocity() {
  float vx, vy = 0;
  vx = (float)cos(angle*PI/180);
  vy = (float)sin(angle*PI/180);
  vx *= speed;
  vy *= speed;
  set_vel(vx, vy);
}

/* Getteurs */
float Ball::get_posX() const{
    return body.GetFX();
}
float Ball::get_posY() const{
    return body.GetFY();
}
float Ball::get_velX() const{
    return body.GetVelX();
}
float Ball::get_velY() const{
    return body.GetVelY();
}
float Ball::get_speed() const{
    return speed;
}
float Ball::get_angle() const{
    return angle;
}

/* Setteurs*/
void Ball::set_angle(float a) { //Définis l'angle de la balle
    angle = a;
    apply_velocity();//On applique les changements.
}

void Ball::set_speed(float s) { //Definis la vitesse de la balle
    speed = s;
    apply_velocity();//On applique les changements.
}

void Ball::set_posX(float x){
    body.SetPosition(x,body.GetFY());
}
void Ball::set_posY(float y){
    body.SetPosition(body.GetFX(),y);
}
void Ball::set_pos(float x,float y){
    set_posX(x);
    set_posY(y);
}

void Ball::set_velX(float x){
    body.SetVelocity(x,body.GetVelY());
}
void Ball::set_velY(float y){
    body.SetVelocity(body.GetVelX(),y);
}
void Ball::set_vel(float x,float y){
    set_velX(x);
    set_velY(y);
}
void Ball::set_vel(int normal) {
	if (normal == 0) { //Left
		if (get_velX() > 0) {
			set_vel(-get_velX(), get_velY());
		}
	}
	if (normal == 2) { //Right
		if (get_velX() < 0) {
			set_vel(-get_velX(), get_velY());
		}
	}
	if (normal == 1) { //Top
		if (get_velY() > 0) {
			set_vel(get_velX(), -get_velY());
		}
	}
	if (normal == 3) { //Bottom
		if (get_velY() < 0) {
			set_vel(get_velX(), -get_velY());
		}
	}
}

/* Change la position de X (X--) ce qui la fait bouger vers la gauche */
void Ball::mv_left(){
    set_pos(get_posX()-1,get_posY());
}
/* Change la position de X (X++) ce qui la fait bouger vers la Droite */
void Ball::mv_right(){
    set_pos(get_posX()+1,get_posY());
}
