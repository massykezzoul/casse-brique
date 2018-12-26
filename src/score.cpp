#include "score.h"
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;


/* Lis le fichier ou sont stocké les meilleurs scores */
/* Si le fichier est inéxistant il sera crée */
Score::Score(string name):size(0){
    /* Compliqué à faire */
    /* Syntaxe du fichier : NOM,SCORE;  */
    ifstream f(name.c_str());
    
    if (!f.fail()){
        string line("");
        string name("");
        int point,i=0;
        while(!f.eof()) {
            getline(f,line);
            name = get_nom(line);
            if (name != "") {
                point = get_point(line);
                if (i < 5) {
                    nom[i] = name;
                    scores[i] = point;
                    ++i;
                    ++size;
                }
            }
        }
    }
}

/* Place le score donnée en paramètre dans sa position */
/* de façon que le tableau reste trié */
void Score::add(Player& p){
    if (size == 0) {
        nom[0] = p.get_name();
        scores[0] = p.get_score();
        size++;
    } else {
        size = (size>=5?5:size+1);
        int i = 0;
        string n("");
        int s = 0;
        while (i<size && scores[i]>p.get_score()){
            ++i;
        }
        string tmpn("");
        int tmps = 0 ;
        n = nom[i];
        s = scores[i];
        nom[i] = p.get_name();
        scores[i] = p.get_score();
        ++i;
        while (i < size) {
            tmpn = nom[i];
            tmps = scores[i];
            
            nom[i] = n;
            scores[i] = s;

            n = tmpn;
            s = tmps;

            ++i;
        }
    }
}

/* suprimme un score du tableau */
void Score::del(int){
    /* j'ai vraiment besoin de ça ? */
}

int Score::get_size() const{
    return size;
}

void Score::print(const Window* w) const{
    int x = w->getX()+10;
    int y = w->getY()+5;
    stringstream ss("");
    Color c = BWHITE;
    for (int i = 0;i<20;++i) w->print(x+i+1,y,' ',c);
    for(int i = 0;i<size;++i ){
        w->print(x,y+i+1,' ',c);
        ss << nom[i] << " : " << scores[i] << " Points   " << endl; ;
        w->print(x+1,y+i+1,ss.str(),c);
    }
}

void Score::write(string nom) const {
    ofstream f(".TMPhightscoreTMP.tmp");
    if (!f.fail()) {
        f.seekp(ios::beg);
        for(int i = 0;i<size;++i) {
            f << nom[i] <<","<< scores[i] << ";" << endl;
        }
    }
    rename(".TMPhightscoreTMP.tmp",nom.c_str());
}


string get_nom(const string &line){
	string nom("");
    unsigned int i = line.find_first_of(",");
    if (i>0 && i < line.size())
        nom = line.substr(0,i);
    return nom;
}
int get_point(const string &line){
    string point("");
    unsigned int i = line.find_first_of(",");
    if (i>0 && i < line.size())
        point = line.substr(i+1);
    return atoi(point.c_str());
   
}

string nettoyer_ligne(string ligne) {
	string sans_comment = ligne;
	// Suppression des commentairess
	sans_comment = sans_comment.substr(0,sans_comment.find_first_of("#"));
;
;
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

	return sans_comment;
}

