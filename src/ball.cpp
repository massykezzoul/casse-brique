#include "Body.h"
#include "ball.h"

using namespace std;

/* Constructeur */

Ball::Ball():posX(10.0),posY(10.0),velX(1.0),velY(0.5),body(posX, posY, velX, velY, WCYAN ,this) {

}

Ball::Ball(int posX,int posY,float velX,float velY,Color c)
    :posX((float)posX),posY((float)posY),velX(velX),velY(velY),body(posX, posY, velX, velY, c, this){

}

Ball::~Ball(){
    
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
