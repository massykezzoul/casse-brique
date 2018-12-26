#ifndef SCORE_H
#define SCORE_H

#include <fstream>
#include "player.h"

class Score {
private:
    std::string nom[5];
    int scores[5];
    int size;

    /* suprimme un score du tableau */
    void del(int);
public:
    /* Lis le fichier ou sont stocké les meilleurs scores */
    /* Si le fichier est inéxistant il sera crée */
    Score(std::string);

    /* Place le score donnée en paramètre dans sa position */
    /* de façon que le tableau reste trié */
    void add(Player&);

    int get_size() const;

    void print(const Window*) const;

    void write(std::string) const;
};

std::string get_nom(const std::string &line);
int get_point(const std::string &line);
std::string nettoyer_ligne(std::string ligne);

#endif