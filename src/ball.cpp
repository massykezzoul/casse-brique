#include "ball.h"
#include <unistd.h>
#include <math.h>

#define PI 3.14159265

using namespace std;

/* Constructeur */

Ball::Ball():posX(10),posY(10),speed(0.1),angle(45),velX(0),velY(0),color(WCYAN),c(' ') {
  apply_velocity();
}

// on donne la vitesse et l'angle de la balle au constructeur !
Ball::Ball(float posX,float posY,float spd,float angl,Color color,char c)
    :posX(posX), posY(posY),speed(spd),angle(angl),velX(0),velY(0),color(color),c(c){
  apply_velocity();
}

Ball::Ball(const Raquette& rq,Color color,char c):posX((2*rq.get_posX()+rq.get_width())/2),posY(rq.get_posY()-1 ),speed(0),angle(0),velX(0),velY(0),color(color),c(c) {}

Ball::Ball(const Ball& b)
    :posX(b.posX), posY(b.posY),speed(b.speed),angle(b.angle),velX(b.velX),velY(b.velY),color(b.color),c(b.c){
  apply_velocity();
}



Ball& Ball::operator=(const Ball &b) {
    if (&b != this) {
        posX = b.posX;
        posY = b.posY;
        speed = b.speed;
        angle = b.angle;
        velX = b.velX;
        velY = b.velY;
        color = b.color;
        c = b.c;
        apply_velocity();
    } 
    return *this;
}


//Grace a l'angle on récupere la velocité x et y avec cos et sin
//on multiplie vx et vy par speed pour avoir la vitesse de la balle.
void Ball::apply_velocity() {
  float vx = 0, vy = 0;
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
Color Ball::get_color() const {
    return color;
}

char Ball::get_char() const {
    return c;
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
    posX = x;
}
void Ball::set_posY(float y){
    posY = y;
}
void Ball::set_pos(float x,float y){
    set_posX(x);
    set_posY(y);
}

void Ball::set_pos(const Raquette &rq){
    set_posX((2*rq.get_posX()+rq.get_width())/2);
    set_posY(rq.get_posY()-1);
}

void Ball::set_velX(float x){
    velX = x;
}
void Ball::set_velY(float y){
    velY = y;
}
void Ball::set_vel(float x,float y){
    set_velX(x);
    set_velY(y);
}
void Ball::set_vel(int normal) {
	if (normal == 4 || normal == 2) { //Left && Right
		if (velX != 0) {
			set_vel(-velX, velY);
		}
	}
	if (normal == 1 || normal == 3) { //Top && Bottom
		if (velY != 0) {
			set_vel(velX, -velY);
		}
	}
}


void Ball::print(const Window* w) const{
	w->print(posX, posY,c);
}

void Ball::clear(const Window* w) const {
    w->print(posX, posY,' ');
}

void Ball::update(Tab_brick& tab,const Raquette& r,Window* w){
    clear(w);
    allCollision(tab,r,w);
    print(w);
}

void Ball::allCollision(Tab_brick& tab,const Raquette& r,Window* w){
    int brick; 
    int bord;
    int raquette;
    bord = collideBord(w);
    set_pos(posX+velX,posY+velY);
    brick = collideBrick(tab,w);
    raquette = collideRaquette(r);
    set_pos(posX-velX,posY-velY);

    if (brick != 0) {
        w->setCouleurBordure(BGREEN);
        set_vel(brick);
        usleep(50000);
        w->setCouleurBordure(BWHITE);
    }
        
    if (bord != 0)
        set_vel(bord);
            
    if (raquette != 0)
        set_vel(raquette);
            
    set_pos(posX+velX,posY+velY);

}
/* Prend un tableau de brick en parametre */
int Ball::collideBrick(Tab_brick& tab,const Window* w) const{
    int i = 0;
    int normal = 0;
    while ( i < tab.get_size() && normal==0 ) {
        normal = collideBrick(*tab.get_brick(i));
        if (normal == 0) ++i;
    }
    if (i >= tab.get_size()) return 0;
    else {
        tab.get_brick(i)->clear(w);
        tab.get_brick(i)->increment_resistance();
        tab.get_brick(i)->print(w);
        tab.get_player()->increment_score(tab.get_brick(i)->get_point());
        if (tab.get_brick(i)->get_resistance() == 0) tab.del(i,w);
        return normal;   
    }
}

int Ball::collideBrick(Brick& b) const{
    if ( (posX) >= b.get_posX() && (posX) < (b.get_posX()+b.get_width()) && (int)(posY) == b.get_posY() )
        return 1;
    else if ( (posY) >= b.get_posY() && (posY) <= (b.get_posY()+b.get_height()) && (int)(posX) == (b.get_posX() + b.get_width()))
        return 2;
    else if( (posX) >= b.get_posX() && (posX) < b.get_posX()+b.get_width() && (int)(posY) == (b.get_posY() + b.get_height()))
        return 3;
    else if ( (posY)>= b.get_posY() && (posY) <= b.get_posY()+b.get_height() && (int)(posX) == b.get_posX())
        return 4;
    else return 0;

}
int Ball::collideRaquette(const Raquette& r) const{
    if ( posX >= r.get_posX() && posX <= r.get_posX()+r.get_width()+1 && (int)posY == r.get_posY())
        return 1;
    else if (posY >= r.get_posY() && posY <= r.get_posY()+r.get_height() && (int)posX == r.get_posX() + r.get_width())
        return 2;
    else if(posX >= r.get_posX() && posX <= r.get_posX()+r.get_width() && (int)(posY) == r.get_posY() + r.get_height())
        return 3;
    else if (posY >= r.get_posY() && posY <= r.get_posY()+r.get_height() && (int)(posX) == r.get_posX())
        return 4;
    else return 0;
}
int Ball::collideBord(const Window* w) const{
    if ( (posX >= w->getX()) && (posX <= w->getX()+w->getLargeur()) && ((int)posY >= (w->getY() + w->getHauteur()) -1 ) )
        return 1;
    else if (posY >= w->getY() && posY < w->getY()+w->getHauteur() && (int)posX <= w->getX())
        return 2;
    else if( (posX >= w->getX()) && (posX < (w->getX()+w->getLargeur())) && ((int)(posY) <= w->getY()))
        return 3;
    else if ( posY >= w->getY() && posY <= w->getY()+w->getHauteur() && (int)(posX) >= w->getX() + w->getLargeur() - 1)
        return 4;
    else return 0;

}

/* ------------------- LA CLASSE TAB_BALL --------------------- */

Tab_ball::Tab_ball():tab(new Ball[3]),size(0),alloc(3) {

}
    
Tab_ball::~Tab_ball(){
    if (tab != NULL  && size > 0) delete[] tab;
}

/* Ajoute une brique au tableau */
void Tab_ball::add(float posX,float posY,float spd,float angl,Color c, char car){
    if (size >= alloc) {
        /* Réallouer 2 fois plus de mémoire */
        if (alloc ==0) alloc = 2; else alloc *= 2;
        Ball* tmp = new Ball[alloc];
        if (tmp == NULL ) exit(1);
        /* Copie des elements précedent */
        for (int i= 0 ; i < size;i++) 
            tmp[i] = tab[i];
        tmp[size] = Ball(posX,posY,spd,angl,c,car);
        ++size;
        Ball* del = tab;
        tab = tmp;
        delete[] del;

    } else {
        /* Il reste encore de l'espace en mémoire */
        tab[size] = Ball(posX,posY,spd,angl,c,car);
        ++size;
    }
}

void Tab_ball::add(const Raquette& rq,Color color,char car){
    if (size >= alloc) {
        /* Réallouer 2 fois plus de mémoire */
        alloc *= 2;
        Ball* tmp = new Ball[alloc];
        if (tmp == NULL ) exit(1);
        /* Copie des elements précedent */
        for (int i= 0 ; i < size;i++) 
            tmp[i] = tab[i];
        tmp[size] = Ball(rq,color,car);
        ++size;
        Ball* del = tab;
        tab = tmp;
        delete[] del;

    } else {
        /* Il reste encore de l'espace en mémoire */
        tab[size] = Ball(rq,color,car);
        ++size;
    }
}
void Tab_ball::del(int i,const Window* w){
    if (i>=size) return;
    else {
        tab[i].clear(w);
        for ( ; i<size-1 ; i++ )
            tab[i] = tab[i+1];
        --size;
    }
}
/* Retourn la brique à la position i*/
Ball* Tab_ball::get_ball(int i){
    if ((i>=size) || (i < 0)) return NULL;
    else return tab+i;
}
int Tab_ball::get_size(){
    return size;
}

void Tab_ball::print(const Window* w) const {
    for (int i=0;i<size;++i) {
        tab[i].print(w);
    }
}

Player* Tab_ball::player;

Player* Tab_ball::get_player() {
    return player;
}

void Tab_ball::set_player(Player* p) {
    player = p;
}