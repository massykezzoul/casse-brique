/*
    La class qui va gérer le joueur
    Kezzoul Massili : massili.kezzoul@etu.umontpellier.fr
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "window.h"

class Player {
private:
    /* data */
    /* Le nom du joueur */
    std::string name;
    /* Nombre de balle restant      */
    int ball;
    /* Le score actuel du joueur    */
    int score;
    /* Le niveau actuel du joueur   */
    int niveau;
    /* Affichage des stats du joureur*/
    Window window;

public:
    /* Constructeur par défault     */
    Player();
    /* Constructeur parametré       */
    Player(std::string,int,int,int);

    Player(int x,int y,int width,int height,Color = BWHITE,Color = WBLACK);

    Player(std::string,int,int,int,int x,int y,int width,int height,Color = BWHITE,Color = WBLACK);

    std::string get_name() const;
    int get_score() const;
    int get_ball() const;
    int get_niveau() const;

    /* Setters */
    void set_name(std::string);
    /* Change le nombre de balle du joueur */
    void set_ball(int);
    /* Incremente le nombre de balle du joueur (Si aucun paramètre donné -> 1 par défault)*/
    /* Donnée un nombre négatif pour décrementer */
    void increment_ball(int = -1);

    /* Change le score du joueur */
    void set_score(int);
    /* Incremente le score du joueur */
    /* Donnée un nombre négatif pour décrementer */
    void increment_score(int);

    /* Change le niveau du joueur */
    void set_niveau(int);
    /* Incremente le niveau du joueur */
    void increment_niveau(int);
    /* Print les informations a l'ecran */
    void print ();

    void clear();

    /* Getters */
};

#endif
