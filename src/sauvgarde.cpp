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

Save::Save(string name,int vie,int score,int niveau,const Tab_brick& t)
    :name(name),vie(vie),score(score),niveau(niveau),tab_brick(t) {

}

string Save::get_name() const {return name;}
int Save::get_vie() const {return vie;}
int Save::get_score() const {return score;}
int Save::get_niveau() const {return niveau;}
Tab_brick Save::get_brick() const{return tab_brick;}

void Save::set_name(const std::string s){
    name = s;
}
void Save::set_vie(const int v){
    vie = v;
}
void Save::set_score(const int s){
    score = s;
}
void Save::set_niveau(const int n){
    niveau = n;
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
            name vie score niveau nombre_brick
            resistance point x y w h color
            resistance point x y w h color
            resistance point x y w h color
            resistance point x y w h color
    */
   string line("");
   string name("");
   int vie,score,niveau,nb_brick;
   /* Tableau de bricks */
   Tab_brick tab_brick;
   /* les attributs de bricks */
   int resistance,point,x,y,w,h;

   int taille,i=0;
   ifstream file(nom_fichier.c_str());
   if (file) {
       file >> taille;
       while(!file.eof() && i< taille) {
            file >> name >> vie >> score >> niveau >> nb_brick;
            /* Lecture des brick */
            tab_brick = Tab_brick();
            for(int j = 0 ; j < nb_brick ; ++j) {
                file >> resistance >> point >> x >> y >> w >> h;
                tab_brick.add(resistance,point,x,y,w,h);
            }
            add(name,vie,score,niveau,tab_brick);
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
            resistance point x y w h
            resistance point x y w h
            resistance point x y w h
            resistance point x y w h
    */
    Tab_brick tab;
    Brick b;
    int s;
    ofstream file(nom_fichier.c_str());
    if (file) {
        file << size << endl;
        for(int i = 0; i < size; i++) {
            file << save[i].get_name() << " " << save[i].get_vie() << " " << save[i].get_score() 
                <<" " << save[i].get_niveau() << " " << save[i].get_brick().get_size() <<endl;
            tab = save[i].get_brick();
            s = tab.get_size();
            for(int j = 0; j < s ; j++) {
                b = *tab.get_brick(j);
                file << b.get_resistance() << " " << b.get_point() 
                    << " " << b.get_posX() << " " << b.get_posY() << " " << b.get_width()
                    << " " << b.get_height() << endl;
            }
        }
        file.close();
    }
}

void Tab_save::add(string name,int vie,int score,int niveau, const Tab_brick& tab) {
    /* copie */
    Save* tmp = new Save[size+1];
    for (int i = 0 ; i < size ; i++)
        tmp[i] = save[i];
    if (save != NULL) delete[] save;
    save = tmp;
    save[size] = Save(name,vie,score,niveau,tab);
    size++;
}

Save Tab_save::get_save(int i) const {
    if (i < size && i >= 0 )
        return save[i];
    else  {
        Save s;
        s.set_name("Erreur");
        return s;
    }
}

int Tab_save::get_size() const{
    return size;
}



/* Supprime la sauvgarde numéro i */
void Tab_save::del(int i){
    if (i >= 0 && i < size) {
        --size;
        for (int j = i ; j < size;j++) {
            save[j] = save[j+1];
        }
    }
}


/* Affiche les partie sauvgardé */
int Tab_save::print(const Window* w) const{
    int x = (int)(0.10*(w->getX()+w->getLargeur()));
    int y = (int)(0.15*(w->getY()+w->getHauteur()));
    Color c = BWHITE;
    stringstream ss("");
    Tab_boutton selection;
    
    Window win(size+5,40,x,y,' ');
    string separateur(win.getLargeur(),'-');
    win.setCouleurBordure(c);
    win.setCouleurFenetre(WBLACK);
    
    if (size == 0 ){
        /* Aucune partie sauvgarder */

        /* Affichage du msg */
        win.print(0,0,separateur);
        win.print(0,1,"Aucune Partie Sauvgardée");
        win.print(0,2,separateur);
        /* Le boutton OK */
        selection.add(" [  OK  ] ",(int)(0.30*(win.getX()+win.getLargeur())),size+4,WBLACK ,c ,true);
        selection.print(&win);
        win.print(0,size+5,separateur);

    } else {
        /* Affichage du msg */
        win.print(0,0,separateur);
        win.print(0,1,"Parties sauvgardées :");
        win.print(0,2,separateur); 
        /* Affichages des scores */
        for(int i = 0;i<size;++i ){
            ss <<i+1<<"-"<<save[i].get_name() << " : " << save[i].get_score() << " Points et " << save[i].get_vie()<< " Balles." << endl;
            selection.add(ss.str(),1,i+3,WBLACK,c,false);
            ss.str("");
            selection.print(&win);
        }
        win.print(0,size+3,separateur);
        /* Le boutton OK */
        selection.add(" [  OK  ] ",(int)(0.30*(win.getX()+win.getLargeur())),size+4,WBLACK ,c ,true);
        selection.print(&win);
        win.print(0,size+5,separateur);
    }

    int car = 0;
    int sel;
    while (car != '\n' && car != 'q' && car != 'Q' && car != ' ' ) {
        car=0;
        do {
            car = getch(); 
            switch (car)
            {
                case KEY_DOWN:
                    selection.down();
                    selection.print(&win);
                    break;
                case KEY_UP:
                    selection.up();
                    selection.print(&win);
                    break;
                case '\n':
                    sel = selection.get_selected();
                    break;
                default:
                    car = ERR;
                    usleep(50000);
                    break;
            }
        } while (c == ERR);
    }
    win.clear();
    return (sel>size?-1:sel-1);
}
