/********************************************************
*  File : Terrain.h
*  Description : Define a simple terrain with borders
*
*
*  Author : Romain Fournier romain.fournier.095@gmail.com
*  20/12/2018
*/

#ifndef __TERRAIN
#define __TERRAIN

#include "window.h"

class Terrain {
  //Attributes
private:
  int posX;
  int posY;
  int width;
  int height;
  Window window;
  //Constructors
public:
  Terrain();
  Terrain(int, int, int, int);
  //Terrain(const Terrain&);
  //Terrain& operator=(const Terrain&);
  //~Terrain();

  //Methods
  int get_posX() const;
  int get_posY() const;
  int get_width() const;
  int get_height() const;

  void set_posX(int);
  void set_posY(int);
  void set_width(int);
  void set_height(int);

  Window* GetWindow ();
  const Window* GetWindow () const;

  void clear ();
};

#endif
