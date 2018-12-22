// Author : Romain Fournier romain.fournier.095@gmail.com
#include <iostream>
#include <unistd.h>

#include "Body.h"
#include "window.h"
#include "LinkedList.h"
#include "brick.h"

using namespace std;

/* List of all Body */
LinkedList<Body>* Body::Objects = new LinkedList<Body>();
Window* Body::window;

/* Creates a Body and adds it into the Objects linked list
*/
Body::Body(int x, int y, int height, int width, Color color, bool solid, bool stationary): x((float)x), y((float)y), velX(0), velY(0), width(width), height(height), color(color), solid(solid), stationary(stationary), brick(NULL), ball(NULL)/*, window(w)*/ {
	/*if (AllColisions()->Lenght() != 0) {//This object overlaps with something
		//TODO, Also remove the parent instance
		//~Body();
	}*/
	Objects->Add(this);
	Draw();
}

Body::Body(int x, int y, int height, int width, Brick* b): x((float)x), y((float)y), velX(0), velY(0), width(width), height(height), color(WRED), solid(true), stationary(true), brick(b), ball(NULL)  {
	Objects->Add(this);
	Draw();
}

Body::Body(int x, int y,float velX, float velY, Color c, Ball* b)
	:x((float)x), y((float)y), velX(velX), velY(velY), width(1), height(1), color(c), solid(true), stationary(false),brick(NULL), ball(b)  {
	Objects->Add(this);
	Draw();
}

Body::~Body() {
	Objects->Rm(this);
}

//GETTERS
int Body::GetX () const { return (int)x; }
int Body::GetY () const { return (int)y; }
float Body::GetFX () const { return x; }
float Body::GetFY () const { return y; }
float Body::GetVelX () const { return velX; }
float Body::GetVelY () const { return velY; }
int Body::GetWidth () const { return width; }
int Body::GetHeight () const { return height; }
Brick* Body::GetBrick () const { return brick; }
Ball* Body::GetBall() const { return ball;}

//SETTERS
void Body::SetVelocity (float vx, float vy) { velX = vx; velY = vy; }
void Body::SetVelocity (int normal) {
	if (normal == 0) { //Left
		if (GetVelX() > 0) {
			SetVelocity(-GetVelX(), GetVelY());
		}
	}
	if (normal == 2) { //Right
		if (GetVelX() < 0) {
			SetVelocity(-GetVelX(), GetVelY());
		}
	}
	if (normal == 1) { //Top
		if (GetVelY() > 0) {
			SetVelocity(GetVelX(), -GetVelY());
		}
	}
	if (normal == 3) { //Bottom
		if (GetVelY() < 0) {
			SetVelocity(GetVelX(), -GetVelY());
		}
	}
}
void Body::SetColor (Color c) { color = c; }
void Body::SetPosition (int x, int y) { SetPosition((float)x, (float)y); }
void Body::SetPosition (float nx, float ny) { x = nx; y = ny; }
void Body::SetWindow (Window* w) { window = w; }
/* Checks if this will collide with b at the next frame
*/
bool Body::Collide (Body* b) {
	if (b == this) {
		return false;
	}
	if (!this->solid || !b->solid) {
		return false;
	}    /* Pour incrementé la valeur de resistance */
    /* La valeur par défault du paramétre est -1 */
	float x1, x2, y1, y2 = 0;
	float bx1, bx2, by1, by2 = 0;

	x1 = GetFX();
	y1 = GetFY();
	x2 = x1 + GetWidth();
	y2 = y1 + GetHeight();

	bx1 = b->GetFX();
	by1 = b->GetFY();
	bx2 = bx1 + b->GetWidth();
	by2 = by1 + b->GetHeight();

	if (x1 > bx2 || x2 < bx1 || y1 > by2 || y2 < by1) {
		return false;
	}
	return true;
}

/* Returns a linked list of all colisions for this body
*/
LinkedList<Body>* Body::AllColisions () {
	LinkedList<Body>* ans = new LinkedList<Body>();
	Objects->ResetPull();
	Body* tmp = Objects->Pull();

	while (tmp != NULL) {
		if (Collide(tmp)) {
			ans->Add(tmp);
		}
		tmp = Objects->Pull();
	}
	return ans;
}

/* Returns the normal of the colision, used to calculate the bounce direction
*/
int Body::CollideNormal (Body* b) {
	if (GetFX() - GetVelX() >= b->GetFX() + b->GetWidth()) {
		return 2;
	}
	if (GetFX() - GetVelX() + GetWidth() <= b->GetFX()) {
		return 0;
	}
	if (GetFY() - GetVelY() >= b->GetFY() + b->GetHeight()) {
		return 3;
	}
	return 1;
}

/* next frame,
* here we change the velocity of non stationary and
* solid bodies that collide with solid
*/
void Body::Update () {
	if (solid && !stationary) {
		LinkedList<Body>* ll = AllColisions();
		if (ll->Lenght() != 0) { //sets the velocity based on all collisions
			Body* current = ll->Pull();
			if (current->GetBrick() != NULL) {
				current->GetBrick()->on_colision();
			}
			while (current != NULL) {
				SetVelocity(CollideNormal(current));
				current = ll->Pull();
			}
		}
		delete ll;
	}
	if (!stationary) {
		SetPosition(GetFX() + GetVelX(), GetFY() + GetVelY());
	}
	Draw ();
}

/* Makes all bodies go one frame forward
*/
void Body::AllUpdate () {
	Objects->ResetPull();
	Body* b = Objects->Pull();
	while (b != NULL) {
		b->Update();
		b = Objects->Pull();
	}
}

/* Draws the body based on its dimentions and coordinates
*/
void Body::Draw () {
	for (int i = GetX(); i < GetX() + GetWidth(); i++) {
		for (int j = GetY(); j < GetY() + GetHeight(); j++) {
			window->print(i, j,' ', color);
		}
	}
}

void Body::RmAll () {
 //Todo
}
