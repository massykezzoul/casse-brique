#ifndef BOUTTON_H
#define BOUTTON_H

#include <string>
#include "../window.h"

class Boutton {
private:   
    int posX;
    int posY;
    std::string text;
    Color no_focus;
    Color on_focus;
    bool focused;

public:
    Boutton();
    Boutton(std::string,int x,int y,Color no_f,Color on_f,bool = false);

    /* Les getteurs */
    int get_posX() const;
    int get_posY() const;
    std::string get_text() const;
    Color get_no_focus() const;
    Color get_on_focus() const;
    bool get_focused() const;

    /* Les setteurs */
    void set_posX(int);
    void set_posY(int);
    void set_pos(int,int);
    void set_text(std::string);
    void set_no_focus(Color);
    void set_on_focus(Color);
    void set_focused(bool = true);

    void print(Window*) const;

    void print(Window*,int,int) const;
};

class Tab_boutton {
private:
    Boutton tab[10];
    int size;
    int selected;
public:
    Tab_boutton();

    void add(std::string,int x,int y,Color,Color,bool = false);
    void print(Window*) const;
    void down();
    void up();

    int get_selected() const;
};

#endif