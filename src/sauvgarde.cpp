#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <cstdlib>

#include "window.h"
#include "brick.h"
#include "boutton/boutton.h"

#include "sauvgarde.h"

using namespace std;

Save::Save():name(""),vie(0),score(0),tab_brick() {

}

Save::Save(string name,int vie,int score,const Tab_brick& t)
    :name(name),vie(vie),score(score),tab_brick(t) {

}

string Save::get_name() const {return name;}
int Save::get_vie() const {return vie;}
int Save::get_score() const {return score;}
const Tab_brick& Save::get_brick() const{return tab_brick;}

void Save::set_name(const std::string s){
    name = s;
}
void Save::set_vie(const int v){
    vie = v;
}
void Save::set_score(const int s){
    score = s;
}
void Save::set_brick(const Tab_brick& t){
    tab_brick = t;
}


void Save::print(const Window* w) const {

}



/* ******************************************************** */

Tab_save::Tab_save(string nom_fichier):save(NULL),size(0) {
    /*
        syntaxe du fichier de sauvgarde :
            name vie score nombre_brick
            forme resistance point x y w h color
            forme resistance point x y w h color
            forme resistance point x y w h color
            forme resistance point x y w h color
    */
   string line("");
   string name("");
   int vie,score,nb_brick;
   /* Tableau de bricks */
   Tab_brick tab_brick;
   /* les attributs de bricks */
   int forme,resistance,point,x,y,w,h,c;

   int taille,i=0;
   ifstream file(nom_fichier.c_str());
   ofstream test("test.txt");
   if (file) {
       file >> taille;
       while(!file.eof() && i< taille) {
            file >> name >> vie >> score >> nb_brick;
            test << name << " v: " << vie << " s: " << score << " b: " << nb_brick << endl;
            /* Lecture des brick */
            for(int i = 0 ; i < nb_brick ; ++i) {
                file >> forme >> resistance >> point >> x >> y >> w >> h >> c;
                tab_brick.add(IntToForme(forme),resistance,point,x,y,w,h,IntToColor(c));
                test << " f: "<<forme <<" r: "<<resistance<<" p: "<<point<<" x: " <<x << " y: "<<y<<" w: "<<w<<" h: "<<h<<" c: "<<c<<endl;
            }
            add(name,vie,score,tab_brick);
            ++i;
       }
       file.close();
   }

}

Tab_save::~Tab_save() {
    if (save != NULL) delete[] save;
}

void Tab_save::write(std::string nom_fichier)const {
   /* Ecrire les element de la classe dans le fichier */

    /*
        syntaxe du fichier de sauvgarde :
            name vie score nombre_brick
            forme resistance point x y w h color
            forme resistance point x y w h color
            forme resistance point x y w h color
            forme resistance point x y w h color
    */
    Tab_brick tab;
    Brick b;
    ofstream file(nom_fichier.c_str());
    if (file) {
        file << size << endl;
        for(int i = 0; i < size; i++) {
            file << save[i].get_name() << " " << save[i].get_vie() << " " << save[i].get_score() 
                << " " << save[i].get_brick().get_size() <<endl;
            tab = save[i].get_brick();
            for(int j = 0; j < tab.get_size() ; j++) {
                b = *tab.get_brick(j);
                file << b.get_forme() << " " << b.get_resistance() << " " << b.get_point() 
                    << " " << b.get_posX() << " " << b.get_posY() << " " << b.get_width()
                    << " " << b.get_height() << " " << b.get_color() << endl;
            }
        }
        file.close();
    }
}

void Tab_save::add(string name,int vie,int score, const Tab_brick& tab) {
    /* copie */
    Save* tmp = new Save[size+1];
    for (int i = 0 ; i < size ; i++)
        tmp[i] = save[i];
    if (save != NULL) delete[] save;
    save = tmp;
    save[size] = Save(name,vie,score,tab);
    size++;
}




/* Supprime la sauvgarde numéro i */
void Tab_save::del(int i){
    if (i < size) {
        --size;
        for (int j = i ; j < size;j++) {
            save[j] = save[j+1];
        }
    }
}


/* Affiche les partie sauvgardé */
void Tab_save::print(const Window* w) const{
    int x = (int)(0.15*(w->getX()+w->getLargeur()));
    int y = (int)(0.15*(w->getY()+w->getHauteur()));
    Color c = BWHITE;
    stringstream ss("");
    
    if (size == 0 ){
        /* Aucune partie sauvgarder */
        Window win(5,35,x,y,' ');
        string separateur(win.getLargeur(),'-');

        win.setCouleurBordure(c);
        win.setCouleurFenetre(WBLACK);
        /* Affichage du msg */
        win.print(0,0,separateur);
        win.print(0,1,"Aucune Partie Sauvgardé");
        win.print(0,2,separateur);
        /* Le boutton OK */
        Boutton ok(" [  OK  ] ",0,WBLACK ,c ,true);
        ok.print(&win,(int)(0.30*(win.getX()+win.getLargeur())),3);

        win.print(0,4,separateur);

        int car = 0;
        while (car != '\n' && car != 'q' && car != 'Q' && car != ' ' ) {
            car = 0;
            car = getch();
            usleep(50000);
        }    
        win.clear();
    } else {
        Window win(size+5,35,x,y,' ');
        string separateur(win.getLargeur(),'-');

        win.setCouleurBordure(c);
        win.setCouleurFenetre(WBLACK);
        /* Affichage du msg */
        ss << "nb : " << size;
        win.print(0,0,separateur);
        win.print(0,1,ss.str());
        win.print(0,2,separateur);
        ss.str("");
        /* Affichages des scores */
        for(int i = 0;i<size;++i ){
            ss << i+1<<"- " <<save[i].get_name() << " : " << save[i].get_score() << " Points et " << save[i].get_vie()<< " Balles." << endl;
            win.print(1,i+3,ss.str());
            ss.str("");
        }
        win.print(0,size+3,separateur);
        /* Le boutton OK */
        Boutton ok(" [  OK  ] ",0,WBLACK ,c ,true);
        ok.print(&win,(int)(0.30*(win.getX()+win.getLargeur())),size+4);

        win.print(0,size+5,separateur);

        int car = 0;
        while (car != '\n' && car != 'q' && car != 'Q' && car != ' ' ) {
            car = 0;
            car = getch();
            usleep(50000);
        }
        win.clear();
    }
}


void nextline(ifstream &file) {
    if (file) {
        char c;
        do file.get(c); while(c != '\n' && !file.eof());
        if (!file.eof()) file.get(c);
    }
}