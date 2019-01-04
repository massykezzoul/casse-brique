#include <string>
#include <algorithm> //transform()
#include <cstdlib>
#include <fstream>
#include <cctype>

#include "config.h"
#include "convert/convert.h"

using namespace std;

/* La classe Config */
/*
Level Config::get_level() const {
	numero = line.size() > 6? stoi(line[6]):0;
					getline(file,line);
					line = clean_line(line);
					while (line != "end-level" && !file.eof()) {
						if (get_key_val(line,key,value)) {

						}
						
						getline(file,line);
						line = clean_line(line);	
					}
}
*/
Ball Config::set_ball(ifstream &file) const {
	float speed = 1.0;
	float angle = -1; // random
	char c='O';
	string key,value,line;

	getline(file,line);
	line = clean_line(line);

	while (!file.eof() && line != "end-ball") {
		if (get_key_val(line,key,value)) {
			if (key == "char" ) c = value[1];
			//else if (key == "color" )
			else if (key == "speed") speed = stof(value);
			else if (key == "angle" && value != "rand") angle = stof(value);
		}

		getline(file,line);
		line = clean_line(line);
	}

	return Ball(10,10,speed,angle,WBLACK,c);
}
Raquette Config::set_raquette(ifstream &file) const {
	int length = 15,speed=3;
	char c = '-';
	string key,value,line;

	getline(file,line);
	line = clean_line(line);

	while (!file.eof() && line != "end-bat") {
		if (get_key_val(line,key,value)) {
			if (key == "char" ) c = value[1];
			//else if (key == "color" )
			else if (key == "speed") speed = stoi(value);
			else if (key == "length") length = stoi(value);
		}

		getline(file,line);
		line = clean_line(line);
	}

	return Raquette(10,20,length,1,speed,WBLACK,c);
}


Config::Config(std::string file_name) {
	ifstream file(file_name.c_str());
	if (file) {
		string line;

		/* Niveau */
		int numero;
		string key,value;

		while ( !file.eof() ) {
			getline(file,line);
			line = clean_line(line);

			if (line != "" ) {
				if ( get_word(line) == "level" ) {
					/* Lecture d'un niveau */
					
				}

				if (get_word(line) == "ball" ) {
					ball = set_ball(file);
				}

				if (get_word(line) == "bat") {
					rq = set_raquette(file);
				}

			}
		}
		file.close();
	}
}

/* Les Getteurs */
Ball Config::get_ball() const {return ball;}
Raquette Config::get_raquette() const {return rq;}


/*-----------------------------------------------*/
/* Les fonction utile pour la lecture du fichier */
/*-----------------------------------------------*/

string clean_line(string ligne){
	string sans_comment = ligne;
	// Suppression des commentairess
	sans_comment = sans_comment.substr(0,sans_comment.find_first_of("#"));

	//supprimer les espaces en plus el tes tabulations
	//supprimer les espaces et les tabulations en debut de chaine
	while ((sans_comment[0] == ' ') || (sans_comment[0] == '\t'))
		sans_comment.erase(0,1);

	//supprimer les espaces et les tabulations en mileux de chaine
	unsigned int i = 1;
	while (i < sans_comment.size()) {
		if ((sans_comment[i] == ' ') && (sans_comment[i-1] == ' '))
	sans_comment.erase(i,1);
		else if (sans_comment[i] == '\t') // remplace les tabulation au milieu par un espace
	sans_comment[i] = ' ';
		else
	++i;
	}

	//suprimer les espaces et les tabulations en fin de chaine 
	while ((sans_comment[sans_comment.size()-1] == ' ') || (sans_comment[sans_comment.size()-1] == '\t'))
		sans_comment.erase(sans_comment.size()-1,1);

	transform(sans_comment.begin(), sans_comment.end(), sans_comment.begin(), ::tolower);
	return sans_comment;
}

string get_word(string ligne,int i){
	int debut,fin;
	debut = i;
	while(ligne[debut] == ' ')
		++debut;

	fin = ligne.find_first_of(" ",debut);
	return ligne.substr(debut,fin-debut);
}

bool decode_shape(std::string valeur,int& x,int& y){
	int i= 0;

	if (!isdigit(valeur[0]))
		return false;

	++i;

	while( (i<valeur.size() ) && (isdigit(valeur[i])))
		++i;
	
	x = stoi(valeur.substr(0,i));

	if( (valeur[i] != 'X') && (valeur[i] != ',') && (valeur[i] != 'x') && (valeur[i] != ' '))
		return false;
	else {

		y = stoi(valeur.substr(++i));

		if (y == -1)
			return false;
		else 
			return true;	
	}
}


bool check_key(string cle,string valeur){
	int x,y;
	if ((cle == "speed") && (isFloat(valeur)))
		return true;
	else if ( (cle == "angle" ) && (isFloat(valeur) || valeur=="rand" ))
		return true;
	else if (( (cle == "resistance" || cle == "nbbricks" || cle == "nblines" || cle == "padding" || cle == "length" ) && (stoi(valeur) > 0)))
		return true;
	else if ((cle == "shape" && (decode_shape(valeur,x,y))))
		return true;
	else if ((cle == "char" && valeur.size() == 3 && valeur[0] == '\'' && valeur[2] == '\'' ))
		return true;
	else 
		return false;
}

bool get_key_val(string ligne,string& cle,string& valeur) {
	ligne = clean_line(ligne);
	/* trouver la clé */
	cle = get_word(ligne);
	/* Il faut vérifié que la clé est conforme */
	/* trouver les deux points */
	if (get_word(ligne,cle.size()) != ":") {
		cle = "";
		valeur = "";
		return false;
	} else {
		int debut = cle.size()+ 3;
		valeur = ligne.substr(debut,ligne.find_first_of(debut)-debut);
		/* il faut verifier que la valeur est correcte par rapport à la clé */
		if (check_key(cle,valeur)) {
			return true;
		} else {
			cle = "";
			valeur = "";
			return false;
		}
	}
}
