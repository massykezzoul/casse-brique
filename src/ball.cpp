#include "Body.h"
#include "ball.h"

#include <math.h>

#define PI 3.14159265

using namespace std;

/* Constructeur */

Ball::Ball():posX(10.0),posY(10.0),velX(1.0),velY(0.5),body(posX, posY, 1, 1, WCYAN, true, false), speed(0.1), angle(45) {
  apply_velocity();
}

// on donne la vitesse et l'angle de la balle au constructeur !
Ball::Ball(int posX,int posY,float spd,float angl,Color c)
    :posX((float)posX),posY((float)posY),velX(0),velY(0),body(posX, posY, 1, 1, c, true, false),speed(spd),angle(angl){
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
    return posX;
}
float Ball::get_posY() const{
    return posY;
}
float Ball::get_velX() const{
    return velX;
}
float Ball::get_velY() const{
    return velY;
}
float Ball::get_speed() const{
    return speed;
}
float Ball::get_angle() const{
    return angle;
}
/* */
float Ball::get_body_posX(){
    return body.GetFX();
}
float Ball::get_body_posY(){
    return body.GetFY();
}
float Ball::get_body_velX(){
    return body.GetVelX();
}
float Ball::get_body_velY(){
    return body.GetVelY();
}
/* */
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
    posX = x;
    body.SetPosition(posX,posY);
}
void Ball::set_posY(float y){
    posY = y;
    body.SetPosition(posX,posY);
}
void Ball::set_pos(float x,float y){
    set_posX(x);
    set_posY(y);
}

void Ball::set_velX(float x){
    velX = x;
    body.SetVelocity(velX,velY);
}
void Ball::set_velY(float y){
    velY = y;
    body.SetVelocity(velX,velY);
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

/* Mise à jour de sa position */
void Ball::update() {
    set_pos(body.GetFX(),body.GetFY());
    set_vel(body.GetVelX(),body.GetVelY());
}
