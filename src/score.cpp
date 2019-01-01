#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>

#include "score.h"
#include "window.h"
#include "boutton/boutton.h"

using namespace std;


/* Lis le fichier ou sont stocké les meilleurs scores */
/* Si le fichier est inéxistant il sera crée */
Score::Score(string name):size(0){
    /* Compliqué à faire */
    /* Syntaxe du fichier : NOM,SCORE;  */
    ifstream f(name.c_str());
    
    if (f){
        string line("");
        string name("");
        int point,i=0;
        while(!f.eof()) {
            getline(f,line);
            name = get_nom(line);
            if (name != "") {
                point = get_point(line);
                if (i < MAX_SCORE) {
                    nom[i] = name;
                    scores[i] = point;
                    ++i;
                    ++size;
                }
            }
        }
    f.close();
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
        size = (size>=MAX_SCORE?MAX_SCORE:size+1);
        int i = 0;
        string n("");
        int s = 0;
        while (i<size && scores[i]>=p.get_score()){
            ++i;
        }
        if (i < MAX_SCORE) {
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
}

int Score::get_size() const{
    return size;
}

void Score::print(const Window* w) const{
    int x = (int)(0.15*(w->getX()+w->getLargeur()));
    int y = (int)(0.15*(w->getY()+w->getHauteur()));
    Color c = BWHITE;
    stringstream ss("");
    Window win(11,35,x,y,' ');

    win.setCouleurBordure(c);
    win.setCouleurFenetre(WBLACK);

    string separateur(win.getLargeur(),'-');
    /* Affichage de titre */
    win.print(0,0,separateur);
    win.print(0,1,"Les Meilleurs Scores :");
    win.print(0,2,separateur);

    /* Affichages des scores */
    for(int i = 0;i<size;++i ){
        ss << nom[i] << " : " << scores[i] << " Points" << endl;
        win.print(1,i+3,ss.str());
        ss.str("");
    }

    win.print(0,MAX_SCORE+3,separateur);
    /* Le boutton OK */
    Boutton ok(" [  OK  ] ",(int)(0.30*(win.getX()+win.getLargeur())),MAX_SCORE+4,WBLACK ,c ,true);
    ok.print(&win);

    win.print(0,MAX_SCORE+5,separateur);

    int car = 0;
    while (car != '\n' && car != 'q' && car != 'Q' && car != ' ' ) {
        car = 0;
        car = getch();
        usleep(50000);
    }
}

void Score::write(string name) const {
    ofstream f(".TMPhightscoreTMP.tmp");
    if (f) {
        for(int i = 0;i<size;++i) {
            f << nom[i]<< ","<< scores[i] <<";" << endl;
        }
    rename(".TMPhightscoreTMP.tmp",name.c_str());
    f.close();
    }
}


/* Utiliser pour la lecture du fichier */ 
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

