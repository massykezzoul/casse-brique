#include "level.h"

Level::Level(){

}
Level::Level(int width_b,int heigth_b,int resistance,int nb_bricks,int nb_lines,int padding){
    int posY = 1;
    int posX = 1;
    for(int line = 0; line < nb_lines ; line++) {
        posX = 1;
        for(int brick = 0 ;brick < nb_bricks ; brick++) {
            bricks.add(resistance,10,posX,posY,width_b,heigth_b);
            posX += width_b+padding;
            // Condition pour ne pas dépasse un niveau critique (atteindre le bord)
        }
        posY += heigth_b+1;
        // Condition pour ne pas dépasse un niveau critique (atteindre la raquette)
    }
}

Tab_brick Level::get_bricks() const{
    return bricks;
}