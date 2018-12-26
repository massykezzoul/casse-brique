#include "raquette.h"

using namespace std;

Raquette::Raquette():posX(10),posY(5),width(10),height(1),vitesse(1),c(WGREEN),car('-'){
    
}

Raquette::Raquette(int posX,int posY,int width,int height,int vitesse,Color c,char cara)
    :posX(posX),posY(posY),width(width),height(height),vitesse(vitesse),c(c),car(cara){
    
}

Raquette::~Raquette(){
    
}

/* Donne la position du coin supérieur gauche de la raquette */
int Raquette::get_posX()const {
    return posX;
}
int Raquette::get_posY()const {
    return posY;
}

/* Donne la largeur et la hauteur de la raquette */
int Raquette::get_width()const {
    return width;
}
int Raquette::get_height()const {
    return height;
}

/* Changer la position du coin supérieur gauche de la raquette */
void Raquette::set_posX(int x){
    posX = (x>0)?x:0;
}
void Raquette::set_posY(int y){
    posY = (y>0)?y:0;
}
void Raquette::set_pos(int x,int y){
    set_posX(x);
    set_posY(y);
}

/* Changer la largeur et la hauteur de la raquette */
/* A définir si besoin */
void Raquette::set_width(int w){
    width = (w>0)?w:1;
}
void Raquette::set_height(int h){
    height = (h>0)?h:1;
}
/* -------------------- */

/* Change la position de X (X--) ce qui la fait bouger vers la gauche */
void Raquette::mv_left(int limite){
    posX -= ((posX-1<limite)?0:(1*vitesse));
    
}
/* Change la position de X (X++) ce qui la fait bouger vers la Droite */
void Raquette::mv_right(int limite){
    posX += ((posX+1+width>limite)?0:(1*vitesse));
}

void Raquette::clear(const Window* w) const {
    for (int i = posX; i < posX + width; i++) {
		for (int j = posY; j < posY + height; j++) {
			w->print(i, j,' ');
		}
	}
}
void Raquette::print(const Window* w) const {
    w->print(posX, posY,'/');
    for (int i = posX+1; i < posX-1 + width; i++) {
		for (int j = posY; j < posY + height; j++) {
			w->print(i, j,car);
		}
	}
    w->print(posX-1+width, posY,'\\');
}