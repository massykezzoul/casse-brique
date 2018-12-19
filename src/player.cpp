#include <string>
#include <iostream>
#include "player.h"

using namespace std;

/* Constructeur par défault     */
Player::Player():name("Unknown"),ball(3),score(0),niveau(0) {
    
}

/* Constructeur parametré   */
Player::Player(string name,int ball,int score,int niveau)
    :name(name),ball(ball>0?ball:0),score(score>0?score:0),niveau(niveau>0?niveau:0) {
    
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

/* Getters */
string Player::get_name(){
    return name;
}
int Player::get_ball(){
    return ball;    
}
int Player::get_score(){
    return score;
}
int Player::get_niveau(){
    return niveau;
}
