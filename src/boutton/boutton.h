#ifndef BOUTTON_H
#define BOUTTON_H

#include <string>
#include "../window.h"

class Boutton {
private:   
    int position;
    std::string text;
    Color no_focus;
    Color on_focus;
    bool focused;

public:
    Boutton();
    Boutton(std::string,int x,Color no_f,Color on_f,bool = false);

    /* Les getteurs */
    int get_pos() const;
    std::string get_text() const;
    Color get_no_focus() const;
    Color get_on_focus() const;
    bool get_focused() const;

    /* Les setteurs */
    void set_pos(int);
    void set_text(std::string);
    void set_no_focus(Color);
    void set_on_focus(Color);
    void set_focused(bool = true);

    void print(Window*) const;

    void print(Window*,int,int) const;
};

class Tab_boutton {
private:
    Boutton tab[4];
    int selected;
public:
    Tab_boutton();
    Tab_boutton(Color,Color);

    void print(Window*) const;
    void down();
    void up();

    int get_selected() const;
};

#endif