// Author : Romain Fournier romain.fournier.095@gmail.com
#include "Terrain.h"
#include "Body.h"
#include "window.h"
#include "brick.h"

Terrain::Terrain(int x, int y, int w, int h): x(x), y(y), w(w), h(h) {
  window = new Window(h, w, x, y, '+');
  window->setCouleurBordure(WBLACK);
  window->setCouleurFenetre(BWHITE);
  Body::SetWindow(window);
  /* Les bordures du terrain */
  new Body(0, 0, 1, w, BRED, true, true);
  new Body(0, 1, h - 1, 1, BRED, true, true);
  new Body(w - 1, 1, h - 1, 1, BRED, true, true);
  /* Bordure du bas */
  new Body(1, h - 1, 1, w - 2, BRED, true, true);
}

Terrain::~Terrain () {
  delete window;
  delete Brick::get_player();
  Body::RmAll();
}

void Terrain::Clear () {
  window->clear();
}

void Terrain::Update () {
  Clear();
  Body::AllUpdate();
}
