#include <iostream>
#include <string>
#include "boutton.h"
#include "../window.h"

using namespace std;

/* ---------------------- CLASS BOUTTON --------------------------- */
Boutton::Boutton():posX(0),posY(0),text("Example"),no_focus(WBLACK),on_focus(WBLACK),focused(false){}

Boutton::Boutton(string txt,int x,int y,Color no_f,Color on_f,bool b)
    :posX(x),posY(y),text(txt),no_focus(no_f),on_focus(on_f),focused(b) {

}

/* Les getteurs */
int Boutton::get_posX() const{
    return posX;
}
int Boutton::get_posY() const{
    return posY;
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
void Boutton::set_posX(int p){
    posX = (p>=0)?p:0;
}
void Boutton::set_posY(int p){
    posY = (p>=0)?p:0;
}
void Boutton::set_pos(int x,int y){
    set_posX(x);
    set_posY(y);
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
    win->print(posX, posY,text,(focused?on_focus:no_focus));
}


/* ---------------------- Tableau de Boutton ---------------------------- */

Tab_boutton::Tab_boutton():size(0),selected(0){}

void Tab_boutton::add(string name,int x,int y,Color fond,Color on_focus,bool select) {
    if (size < 10){
        if (select) selected = size;
        tab[size] = Boutton(name,x,y,fond,on_focus,select);
        ++size;
    }
}

void Tab_boutton::print(Window* win) const{
    for(int i =0 ; i < size; i++) {
        tab[i].print(win);
    }    
}

void Tab_boutton::down(){
    tab[selected].set_focused(false);
    selected = (selected < size-1 ? selected+1 : 0);
    tab[selected].set_focused(true);
}
void Tab_boutton::up(){
    tab[selected].set_focused(false);
    selected = ( selected > 0 ?selected-1:size-1);
    tab[selected].set_focused(true);
}

int Tab_boutton::get_selected() const {
    return selected+1;
}