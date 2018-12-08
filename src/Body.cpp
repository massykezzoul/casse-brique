// Author : Romain Fournier romain.fournier.095@gmail.com
#include <iostream>

#include "window.h"
#include "LinkedList.h"
#include "Body.h"

using namespace std;

LinkedList<Body>* Body::Objects = new LinkedList<Body>();

Body::Body(int x, int y, int height, int width, Color color, char ch, bool solid, bool stationary): x((float)x), y((float)y), width(width), height(height), velX(0), velY(0), color(color), ch(ch), solid(solid), stationary(stationary) {
	/*if (AllColisions()->Lenght() != 0) {//This object overlaps with something
		//TODO, Also remove the parent instance
		//~Body();
	}*/
	Objects->Add(this);
	window = new Window(1, 1, 1, 1, ' ');
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

void Body::SetPosition (float nx, float ny) {
	x = nx;
	y = ny;
}

bool Body::Collide (Body* b) {
	if (b == this) {
		return false;
	}
	if (!this->solid || !b->solid) {
		return false;
	}
	float x1, x2, y1, y2 = 0;
	float bx1, bx2, by1, by2 = 0;

	x1 = GetFX() + GetVelX();
	y1 = GetFY() + GetVelY();
	x2 = x1 + GetWidth();
	y2 = y1 + GetHeight();

	bx1 = b->GetFX();
	by1 = b->GetFY();
	bx2 = bx1 + b->GetWidth();
	by2 = by1 + b->GetHeight();

	if (x1 > bx2 || x2 < bx1 || y1 > by2 || y2 < by1) {
		return false;
	}
		std::cout << "A" << std::endl;
	return true;
}

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

int Body::CollideNormal (Body* b) {
	if (GetFX() >= b->GetFX() + b->GetWidth()) {
		return 2;
	}
	if (GetFX() + GetWidth() <= b->GetFX()) {
		return 0;
	}
	if (GetFY() >= b->GetFY() + b->GetHeight()) {
		return 3;
	}
	return 1;
}

void Body::Update () {
	if (solid && !stationary) {
		LinkedList<Body>* ll = AllColisions();
		if (ll->Lenght() != 0) {
			int normal = CollideNormal(ll->Get(0));
			std::cout << "Normal " << normal << std::endl;
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

void Body::AllUpdate () {
	Objects->ResetPull();
	Body* b = Objects->Pull();
	while (b != NULL) {
		b->Update();
		b = Objects->Pull();
	}
}

void Body::Draw () {
	delete window;
	window = new Window(height, width, x, y, ' ');
	window->setCouleurFenetre(color);
	window->setCouleurBordure(WBLACK);
}
