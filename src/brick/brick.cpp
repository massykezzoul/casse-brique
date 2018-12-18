#include <iostream>
#include "brick.h"

using namespace std; 

/* Constructeur */ 
Brick::Brick():forme(CARRE),resistance(1),point(10) {

}

Brick::Brick(Forme f,int r,int p):forme(f),resistance(r>0?r:0),point(p>0?p:0){

}
/* Destructeur */
Brick::~Brick() {
    forme = NB_FORME;
    resistance = 0;
    point = 0;
}

/* Les getteurs */
Forme Brick::get_forme() const{
    return forme;
}
int Brick::get_resistance() const{
    return resistance;
}
int Brick::get_point() const{
    return point;
}

/*  Les setteurs */
void Brick::set_forme(Forme f){
    forme = f;
}
void Brick::set_resistance(int r){
    resistance = (r > 0)?r:0;
}
void Brick::set_point(int p){
    point = (p>0)?p:0;
}

/* Pour incrementé la valeur de resistance */
/* La valeur par défault du paramétre est -1 */
void Brick::increment_resistance(int r){
    resistance += r;
    resistance = (resistance<0)?0:resistance;

}