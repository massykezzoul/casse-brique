/********************************************************
*  File : Body.h
*  Description : Used to give an object physical
*  properties, and to print a body to the screen.
*
*  Colision normals :
*
*  011112
*  0====2
*  033332
*
*  Author : Romain Fournier romain.fournier.095@gmail.com
*  4/12/2018
*/

#ifndef __PHYSIQUE
#define __PHYSIQUE

#include "window.h"
#include "LinkedList.h"

using namespace std;

class Brick;
class Ball;

class Body {
	//Attributes
private:
	float x;
	float y;
	float velX;
	float velY;
	int width;
	int height;
	Color color;
	bool solid;
	bool stationary;
	Brick* brick;
	Ball* ball;
	static Window* window;
	static LinkedList<Body>* Objects;
	//Constructors
public:
	Body(int x, int y, int height, int width, Color color, bool solid, bool stationary);
	Body(int x, int y, int height, int width, Brick* b);
	/* Une Balle */
	Body(int x, int y, float velX, float velY, Color c ,Ball*);
	~Body();
	//Methods
public:
	static void AllUpdate ();
	int GetX () const;
	int GetY () const;
	float GetFX () const;
	float GetFY () const;
	float GetVelX () const;
	float GetVelY () const;
	int GetWidth () const;
	int GetHeight () const;
	Brick* GetBrick () const;
	Ball* GetBall() const;
	static void SetWindow (Window* w);
	void SetVelocity (float, float);
	void SetVelocity (int);
	void SetPosition (float, float);
	void SetPosition (int, int);
	void SetColor (Color);
	LinkedList<Body>* AllColisions ();
	bool Collide (Body*);
	int CollideNormal (Body*); //0 Left, 1 Top, 2 Right, 3 Bottom, -1 No collisions
	void Update ();
	void Draw ();
	static void RmAll (); //frees the whole LinkedList
};

#endif
