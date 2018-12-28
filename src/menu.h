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
        2 : vers Options
        3 : vers Scores
        4 : Quitter
*/

void jouer();
/*   
    La Partie commence ici
*/  

void score();
/* 
    Affiche les scores sauvgarder
*/

void option();
/*
    Pour changer les options du programme
*/

#endif