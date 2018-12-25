// Author : Romain Fournier romain.fournier.095@gmail.com
#include "Terrain.h"
#include "Body.h"
#include "window.h"
#include "brick.h"

Terrain::Terrain(int x, int y, int w, int h): posX(x), posY(y), width(w), height(h) {
  window = new Window(h, w, x, y, '+');
  window->setCouleurBordure(WBLACK);
  window->setCouleurFenetre(BWHITE);
  Body::SetWindow(window);
  /* Les bordures du terrain */
  new Body(0, 0, 1, w, BRED, true, true);
  new Body(0, 1, h - 1, 1, BRED, true, true);
  new Body(w - 1, 1, h - 1, 1, BRED, true, true);
  /* Bordure du bas (enever pour permettre à la balle de sortir du terrain) */
  new Body(1, h - 1, 1, w - 2, BRED, true, true);
}

Terrain::~Terrain () {
  delete window;
  delete Brick::get_player();
  Body::RmAll();
}

int Terrain::get_posX() const {
  	return posX;
}
int Terrain::get_posY() const {
  	return posY;
}
int Terrain::get_width() const {
  	return width;
}
int Terrain::get_height() const {
  	return height;
}

void Terrain::set_posX(int x) {
  	posX = (x>=0)?x:0;
}
void Terrain::set_posY(int y) {
  	posY = (y>=0)?y:0;
}
void Terrain::set_width(int w) {
	width = (w>=0)?w:10;
}
void Terrain::set_height(int h) {
	height = (h>=0)?h:10;
}

void Terrain::clear () {
  window->clear();
}

void Terrain::Update () {
  clear();
  Body::AllUpdate();
}
