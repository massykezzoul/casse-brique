#include "raquette.h"

using namespace std;

Raquette::Raquette():body(10,5,1,10,WCYAN,true,true){
    
}

Raquette::Raquette(int posX,int posY,int width,int height, Color c):
    body(posX,posY,width,height,c,true,true) {
    
}

Raquette::~Raquette(){
    
}

/* Donne la position du coin supérieur gauche de la raquette */
float Raquette::get_posX(){
    return body.GetFX();
}
float Raquette::get_posY(){
    return body.GetFY();
}

/* Donne la largeur et la hauteur de la raquette */
int Raquette::get_width(){
    return body.GetWidth();
}
int Raquette::get_height(){
    return body.GetHeight();
}

/* Changer la position du coin supérieur gauche de la raquette */
void Raquette::set_posX(float x){
    if (x<0) {
        exit(1);
    }
    body.SetPosition(x,get_posY());
}
void Raquette::set_posY(float y){
    if (y<0) {
        exit(1);
    }
    body.SetPosition(get_posX(),y);
}
void Raquette::set_pos(float x,float y){
    set_posX(x);
    set_posY(y);
}

/* Changer la largeur et la hauteur de la raquette */
/* A définir si besoin */
void Raquette::set_width(int w){
    
}
void Raquette::set_height(int h){
    
}
/* -------------------- */

/* Change la position de X (X--) ce qui la fait bouger vers la gauche */
void Raquette::mv_letf(){
    body.SetPosition(get_posX()-1,get_posY());
}
/* Change la position de X (X++) ce qui la fait bouger vers la Droite */
void Raquette::mv_right(){
    body.SetPosition(get_posX()+1,get_posY());    
}