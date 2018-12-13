// Author : Romain Fournier romain.fournier.095@gmail.com
#include <iostream>
#include <unistd.h>

#include "window.h"
#include "LinkedList.h"
#include "Body.h"

using namespace std;

/* List of all Body */
LinkedList<Body>* Body::Objects = new LinkedList<Body>();

/* Creates a Body and adds it into the Objects linked list
*/
Body::Body(int x, int y, int height, int width, Color color, char ch, bool solid, bool stationary, Window* w): x((float)x), y((float)y), width(width), height(height), velX(0), velY(0), color(color), ch(ch), solid(solid), stationary(stationary)/*, window(w)*/ {
	/*if (AllColisions()->Lenght() != 0) {//This object overlaps with something
		//TODO, Also remove the parent instance
		//~Body();
	}*/
	window = w;
	Objects->Add(this);
	Draw();
}

//GETTERS
int Body::GetX () { return (int)x; }
int Body::GetY () { return (int)y; }
float Body::GetFX () { return x; }
float Body::GetFY () { return y; }
float Body::GetVelX () { return velX; }
float Body::GetVelY () { return velY; }
int Body::GetWidth () { return width; }
int Body::GetHeight () { return height; }

//SETTERS
void Body::SetVelocity (float vx, float vy) { velX = vx; velY = vy; }
void Body::SetColor (Color c) { color = c; }
void Body::SetPosition (int x, int y) { SetPosition((float)x, (float)y); }
void Body::SetPosition (float nx, float ny) { x = nx; y = ny; }

/* Checks if this will collide with b at the next frame
*/
bool Body::Collide (Body* b) {
	if (b == this) {
		return false;
	}
	if (!this->solid || !b->solid) {
		return false;
	}
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
		if (ll->Lenght() != 0) {
			int normal = CollideNormal(ll->Get(0));
			if (normal == 0 || normal == 2) {
				SetVelocity(-GetVelX(), GetVelY());
				ll->Get(0)->SetVelocity(-ll->Get(0)->GetVelX(), ll->Get(0)->GetVelY());
			} else {
				SetVelocity(GetVelX(), -GetVelY());
				ll->Get(0)->SetVelocity(ll->Get(0)->GetVelX(), -ll->Get(0)->GetVelY());
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
			window->print(i, j, ' ', color);
		}
	}
}
