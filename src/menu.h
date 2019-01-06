#ifndef MENU_H
#define MENU_H

#include "window.h"
#include <string>


int menu(Color fond = WBLACK,Color bordure = BWHITE);
/*   
    Affiche le Menu principal en debut de partie
    Contient les boutton suivant :
        - Joueur
        - Opions
        - Scores
        - Quiter

    Retourne un entier entre 0 et 4 :
        0 : ERREUR
        1 : vers jouer
        2 : vers charger
        3 : vers Options
        4 : vers Scores
        5 : Quitter
*/

void jouer(std::string config_file , int = -1);
/*   
    La Partie commence ici
*/  

int charger();
/* 
    Charger une partie sauvgarder
*/
void score();
/* 
    Affiche les scores sauvgarder
*/

void option();
/*
    Pour changer les options du programme
*/

void option_ball();

void option_raquette();

#endif