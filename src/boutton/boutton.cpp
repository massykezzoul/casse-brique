#include <iostream>
#include <string>
#include "boutton.h"
#include "../window.h"

using namespace std;

/* ---------------------- CLASS BOUTTON --------------------------- */
Boutton::Boutton():position(0),text("Example"),no_focus(WBLACK),on_focus(WBLACK),focused(false){}

Boutton::Boutton(string txt,int x,Color no_f,Color on_f,bool b)
    :position(x),text(txt),no_focus(no_f),on_focus(on_f),focused(b) {

}

/* Les getteurs */
int Boutton::get_pos() const{
    return position;
}
string Boutton::get_text() const{
    return text;
}
Color Boutton::get_no_focus() const{
    return no_focus;
}
Color Boutton::get_on_focus() const{
    return on_focus;
}
bool Boutton::get_focused() const{
    return focused;
}

/* Les setteurs */
void Boutton::set_pos(int p){
    position = (p>=0)?p:0;
}
void Boutton::set_text(string txt){
    text = txt;
}
void Boutton::set_no_focus(Color c){
    no_focus = c;
}
void Boutton::set_on_focus(Color c){
    on_focus = c;
}
void Boutton::set_focused(bool b){
    focused = b;
}

void Boutton::print(Window* win) const{
    win->print( (win->getX()+win->getLargeur()) / 2  - 6, 8 + position,text,(focused?on_focus:no_focus));
}

void Boutton::print(Window* w,int x,int y) const {
    w->print(x,y,text,(focused?on_focus:no_focus));
}


/* ---------------------- Tableau de Boutton ---------------------------- */

Tab_boutton::Tab_boutton():selected(0){}


Tab_boutton::Tab_boutton(Color fond, Color on_focus) {
    tab[0] = Boutton("Jouer",1,fond,on_focus,true);
    tab[1] = Boutton("Charger",2,fond,on_focus);
    tab[2] = Boutton("Options",3,fond,on_focus);
    tab[3] = Boutton("Scores",4,fond,on_focus);
    tab[4] = Boutton("Quitter",5,fond,on_focus);
    selected = 0;
}

void Tab_boutton::print(Window* win) const{
    for(int i =0 ; i < 5; i++) {
        tab[i].print(win);
    }    
}
void Tab_boutton::down(){
    tab[selected].set_focused(false);
    selected = (selected < 4 ? selected+1 : 0);
    tab[selected].set_focused(true);
}
void Tab_boutton::up(){
    tab[selected].set_focused(false);
    selected = ( selected > 0 ?selected-1:4);
    tab[selected].set_focused(true);
}

int Tab_boutton::get_selected() const {
    return selected+1;
}