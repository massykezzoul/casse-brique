#include <iostream>
#include "window.h"
#include "brick.h"

using namespace std;


/* Constructeur */
Brick::Brick():forme(CARRE),resistance(1),point(10), x(0),y(0), width(2), height(3),c(WRED) {

}

Brick::Brick(Forme f,int r,int p, int x, int y,int w,int h,Color c):forme(f),resistance(r>0?r:0),point(p>0?p:0), x(x),y(y) ,width(w), height(h),c(c) {

}

Brick::Brick(const Brick& b)
    :forme(b.forme),resistance(b.resistance),point(b.point),x(b.x),y(b.y),width(b.width),height(b.height),c(b.c){

}

Brick& Brick::operator=(const Brick &b) {
    if (&b != this) {
        forme = b.forme;
        resistance = b.resistance;
        point = b.point;
        x = b.x;
        y = b.y;
        width = b.width;
        height = b.height;
        c = b.c;
    } 
    return *this;
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
int Brick::get_posX() const {
    return x;
}
int Brick::get_posY() const {
    return y;
}
int Brick::get_width() const {
    return width;
}
int Brick::get_height() const {
    return height;
}

Color Brick::get_color()const {
    return c;
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
void Brick::increment_resistance(int r) {
    resistance += r;
    resistance = (resistance<0)?0:resistance;
}

void Brick::clear(const Window* w) const {
    for (int i = x; i < x + width; i++) {
		for (int j = y; j < y + height; j++) {
			w->print(i, j,' ');
		}
	}
}

void Brick::print(const Window* w)const {
    for (int i = x; i < x + width; i++) {
		for (int j = y; j < y + height; j++) {
			w->print(i, j,' ',c);
		}
	}
}


/* ------------------- LA CLASSE TAB_BRICK --------------------- */

Tab_brick::Tab_brick():tab(NULL),size(0),alloc(0) {

}

Tab_brick::Tab_brick(const Tab_brick& b)
    :tab(new Brick[b.alloc]),size(b.size),alloc(b.alloc){
    for(int i = 0; i < size; i++) {
        tab[i] = b.tab[i];
    }
    
}

Tab_brick& Tab_brick::operator=(const Tab_brick &b) {
    if (&b != this) {
        size = b.size;
        alloc = b.alloc;
        if (tab != NULL) delete[] tab;
        delete tab;
        tab = new Brick[b.alloc];
        for(int i =0; i < size ; ++i) {
            tab[i] = b.tab[i];
        }
    } 
    return *this;
}



    
Tab_brick::~Tab_brick(){
    if (alloc > 0) delete[] tab;
}

/* Ajoute une brique au tableau */
void Tab_brick::add(Forme f,int resistance,int point,int x,int y,int w,int h,Color c){
    if (size >= alloc) {
        /* Réallouer 2 fois plus de mémoire */
        if (alloc ==0) alloc = 2; else alloc *= 2;
        /* Copie des elements précedent */
        Brick* tmp = new Brick[alloc];
        if (tmp == NULL ) exit(1);
        for (int i= 0 ; i < size;i++) 
            tmp[i] = tab[i];
        delete[] tab;
        tab = tmp;
        tab[size] = Brick(f,resistance,point,x,y,w,h,c);
        ++size;
    } else {
        /* Il reste encore de l'espace en mémoire */
        tab[size] = Brick(f,resistance,point,x,y,w,h);
        ++size;
    }
}
void Tab_brick::del(int i,const Window* w){
    if (i>=size) return;
    else {
        tab[i].clear(w);
        for ( ; i<size-1 ; i++ )
            tab[i] = tab[i+1];
        --size;
    }
}
/* Retourn la brique à la position i*/
Brick* Tab_brick::get_brick(int i){
    if (i>=size) return NULL;
    else return tab+i;
}
int Tab_brick::get_size(){
    return size;
}

void Tab_brick::print(const Window* w) const {
    for (int i=0;i<size;++i) {
        tab[i].print(w);
    }
}

Player* Tab_brick::player;

Player* Tab_brick::get_player() {
    return player;
}

void Tab_brick::set_player(Player* p) {
    player = p;
}


/*---------------------------------------------------------*/

int FormeToInt(Forme f) {
    return (int)f;
}

Forme IntToForme(int i) {
    switch(i) {
        case 0:
            return CARRE;
            break;
        case 1:
            return TRIANGLE;
            break;
        case 2:
            return CREUSE;
            break;
        case 3:
            return RONDE;
            break;
        default:
            return NB_FORME;
            break;
    } 
}
