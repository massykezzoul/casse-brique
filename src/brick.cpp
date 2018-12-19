#include <iostream>
#include "window.h"
#include "Body.h"
#include "brick.h"

using namespace std;

/* Constructeur */
Brick::Brick():forme(CARRE),resistance(1),point(10), x(0), y(0) {
  Body b(x, y, 3, 2, WRED, ' ', true, true);
  body = b;
}

Brick::Brick(Forme f,int r,int p, int x, int y):forme(f),resistance(r>0?r:0),point(p>0?p:0), x(x), y(y){
  Body b(x, y, 3, 2, WRED, ' ', true, true);
  body = b;
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

void Brick::set_player(Player p) {
  player = p;
}

/* Pour incrementé la valeur de resistance */
/* La valeur par défault du paramétre est -1 */
void Brick::increment_resistance(int r){
    resistance += r;
    resistance = (resistance<0)?0:resistance;

}

void Brick::on_colision () {
  increment_resistance(-1);
  if (get_resistance <= 0) {
    player.increment_score(get_point());
    ~Brick();
  }
}
