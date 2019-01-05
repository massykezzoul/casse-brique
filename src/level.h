#ifndef LEVEL_H
#define LEVEL_H

#include "brick.h"

class Level {
private:
    Tab_brick bricks;
public:
    Level();
    Level(int width_b,int heigth_b,int resistance,int nb_bricks,int nb_lines,int padding);

    Tab_brick get_bricks() const;
    
};

#endif