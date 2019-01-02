#ifndef SAUVGARDE_H
#define SAUVGARDE_H

#include "window.h"
#include "brick.h"


class Save {
private:
    /* Nombre de partie sauvgardé */
    std::string name;
    int vie;
    int score;
    int niveau;
    Tab_brick tab_brick;

public:
    Save();
    /* On donne au constructeur le nom (ou le chemin) du fichier où sont stocké les partie */
    Save(std::string name,int vie,int score,int niveau,const Tab_brick&);

    /* retourne les infomarion pour chargé la partie dont le numéro est donnée en paramètre */
    std::string get_name() const;
    int get_vie() const;
    int get_score() const;
    int get_niveau() const;
    Tab_brick get_brick() const;

    void set_name(const std::string);
    void set_vie(const int);
    void set_score(const int);
    void set_niveau(const int);
    void set_brick(const Tab_brick&);

    /* Affiche les partie sauvgardé */
    void print(const Window*) const;
};

#define NB_SAUVGARDE_MAX 100

class Tab_save{
private:
    Save* save;
    int size;

public:
    Tab_save(std::string file);
    ~Tab_save();


    void write(std::string file) const;

    void add(std::string,int vie,int score,int niveau,const Tab_brick&);

    Save get_save(int i) const;

    int get_size() const;
 
    void del(int i);

    int print(const Window*) const;

};

#endif