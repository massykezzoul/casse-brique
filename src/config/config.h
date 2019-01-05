#ifndef _CONFIG
#define _CONFIG

#include "../ball.h"
#include "../raquette.h"
#include "../level.h"

class Config {
private:
	int nb_niveau;
    Level* niveau;
    Ball ball;
    Raquette rq;

    Level set_level(std::ifstream&) const;
    Ball set_ball(std::ifstream&) const;
    Raquette set_raquette(std::ifstream&) const;

public:

    Config(std::string file_name);

    Ball get_ball() const;
    Raquette get_raquette() const;
	Level get_level(int i) const;
	int get_size() const;
};


/* Les fonction utile pour lire le fichier de configuration */

std::string clean_line(std::string ligne);
/*
	on enleve les espaces inutiles et les commentaires de la ligne donnée en paramètre
    et met tout les mots en miniscule
*/

std::string get_word(std::string,int = 0);
/*
	Extrait à partir de la chaine donné en paramètre, le premier mot trouvé 
	à partir de i, (par défault i = 0)
*/

bool decode_shape(std::string valeur,int& x,int& y);
/*
	Données  : 	valeur qui vient après la clé "Shape",
	Resultats: 	Vrai si est dans le format "01x02" || "01 02" || "01,02"
									Renvoie ^x=01  &&     ^y=02
 			Faux sinon
*/

bool check_key(std::string cle,std::string valeur);
/*
	renvoie true si la cle est correct ET la valeur est aproprié à la clé donnée
	par exemple : 	si cle = "NbBricks" et la valeur est un entier alors la methode renvoie true
*/

bool get_key_val(std::string ligne,std::string& cle,std::string& valeur);
/*
	Renvoie true si le couple 'cle : valeur' existe 
	renvoie false sinon et les chaines cle,valeur seront vide
*/



#endif