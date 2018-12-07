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
	Window window;
	static LinkedList<Body> Objects;
	//Constructors
public:
	Body(int x, int y, int heigth, int width, Color color, char ch=' ');
	Body(int x, int y, float heigth, float width, Color color);
	//Methods
public:
	int GetX ();
	int GetY ();
	float GetFX ();
	float GetFY ();
	float GetVelX ();
	float GetVelY ();
	int GetWidth ();
	int GetHeight ();
	void SetVelocity (float, float);
	void SetPosition (float, float);
	void SetPosition (int, int);
	void SetColor (color);
	LinkedList<Body> AllColisions ();
	bool Collide (Body);
	int CollideNormal (Body); //0 Left, 1 Top, 2 Right, 3 Bottom
	void Move ();
};

#endif