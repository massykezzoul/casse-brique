#include <string>
#include <sstream>
#include <iostream>
#include "player.h"
#include "window.h"

using namespace std;

/* Constructeur par défault     */
Player::Player():name("Unknown"),ball(3),score(0),niveau(0),window(1, 1, 0, 0, ' ') {
  window.setCouleurBordure(WBLACK);
  window.setCouleurFenetre(BWHITE);
}

/* Constructeur parametré   */
Player::Player(string name,int ball,int score,int niveau)
    :name(name),ball(ball>0?ball:0),score(score>0?score:0),niveau(niveau>0?niveau:0),window(25, 25, 51, 0, ' ')  {
      window.setCouleurBordure(WBLACK);
      window.setCouleurFenetre(BWHITE);
}

Player::Player(int x,int y,int width,int height,Color bord,Color fenetre):name("Unknown"),ball(3),score(0),niveau(0),window(height, width, x, y, ' ') {
    window.setCouleurBordure(bord);
    window.setCouleurFenetre(fenetre);
}

Player::Player(std::string name,int ball,int score,int niveau,int x,int y,int width,int height,Color bord,Color fenetre)
    :name(name),ball(ball>0?ball:0),score(score>0?score:0),niveau(niveau>0?niveau:0),window(height, width, x, y, ' ') {
    window.setCouleurBordure(bord);
    window.setCouleurFenetre(fenetre);
}

string Player::get_name() const {
    return name;
}

int Player::get_score() const {
    return score;
}

int Player::get_ball() const {
    return ball;
}

int Player::get_niveau() const {
    return niveau;
}
Window Player::get_window() const{
    return window;
}

/* Setters */
void Player::set_name(string n){
    name = n;
}
/* Change le nombre de balle du joueur */
void Player::set_ball(int b){
    ball = (b<0 ? 0 : b);
}
/* Incremente le nombre de balle du joueur (Si aucun paramètre donné -> 1 par défault)*/
/* Donnée un nombre négatif pour décrementer */
void Player::increment_ball(int b){
    ball = (ball+b < 0) ? 0 : ball+b;
}

/* Change le score du joueur */
void Player::set_score(int s){
    score = (s<0 ? 0 : s);
}
/* Incremente le score du joueur */
/* Donnée un nombre négatif pour décrementer */
void Player::increment_score(int s){
    score = (score < -s) ? 0 : score+s;
}

/* Change le niveau du joueur */
void Player::set_niveau(int n){
    niveau = (n<0 ? 0 : n);
}
/* Incremente le niveau du joueur */
void Player::increment_niveau(int n){
    niveau = (niveau < -n) ? 0 : niveau+n ;
}

/* Print les informations */
void Player::print(){
  window.clear();
  stringstream ss;
  ss.str("");
  ss << "Niveau: " << get_niveau();
  window.print(10, 1, ss.str());
  ss.str("");
  ss << "Nom: " << get_name();
  window.print(3, 2, ss.str());
  ss.str("");
  ss << "Points: " << get_score();
  window.print(3, 3, ss.str());
  ss.str("");
  ss << "Vies: " << get_ball();
  window.print(3, 4, ss.str());
}

void Player::clear(){
    window.clear();
}