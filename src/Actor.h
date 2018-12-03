#ifndef _ACTOR
#define _ACTOR

typedef enum enumcolor enumcolor;
enum enumcolor {
  RED = 0, GREEN, BLUE, YELLOW, BLACK, WHITE;
};

class Actor {
  //ATTRIBUTS
 private:
  int x;
  int y;
  int width;
  int height;
  int color;
  static Actor actorList;
  //CONSTRUCTEURS
 public:
  Actor();
  Actor(int x, int y);
  Actor(int x, int y, int width, int height);
  Actor(int x, int y, int width, int height, int color);
  ~Actor();
  //METHODES
 public:
  //Get
  int GetX();
  int GetY();
  int GetWidth();
  int GetHeight();
  int GetColor();
  //Set
  bool SetX(int x);
  bool SetY(int y);
  bool SetWidth(int width);
  bool SetHeight(int height);
  bool SetColor(int color);
  //
  void Print();
  bool Collide(Actor a);
  
};

#endif
