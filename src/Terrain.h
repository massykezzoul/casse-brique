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
  int x;
  int y;
  int w;
  int h;
  Window* window;
  //Constructors
public:
  Terrain(int, int, int, int);
  ~Terrain();
  //Methods
public:
  Window GetWindow ();
  void Clear ();
  void Update ();
};

#endif
