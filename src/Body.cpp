// Author : Romain Fournier romain.fournier.095@gmail.com
#include "Body.h"
#include "window.h"
#include "LinkedList.h"

Body::Body(int x, int y, int height, int width, Color color, char ch=' ', bool solid, bool stationary): x((float)x), y((float)y), width(width), height(height)
																																										 , velX(0), velY(0), color(color), ch(ch), solid(solid), stationary(stationary) {
	if (AllColisions().Lenght() != 0) {//This object overlaps with something
		//TODO, Also remove the parent instance
		~Body();
	}
	Window tmp(height, width, x, y, ch);
	window = tmp;
}

//GETTERS
int Body::GetX () { return (int)X; }
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
bool Body::SetPosition (int x, int y) { SetPosition((float)x, (float)y); }

bool Body::SetPosition (float nx, float ny) {
	float tx = GetFX();
	float ty = GetFY();
	x = nx;
	y = ny;
	if (AllColisions().Lenght() == 0) {
		return true;
	}
	x = tx;
	y = ty;
	return false;
}

bool Body::Collide (Body b) {
	float x1, x2, y1, y2 = 0;
	float bx1, bx2, by1, by2 = 0;

	x1 = GetFX();
	y1 = GetFY();
	x2 = x1 + GetWidth();
	y2 = y1 + GetHeight();

	bx1 = b.GetFX();
	by1 = b.GetFY();
	bx2 = bx1 + b.GetWidth();
	by2 = by1 + b.GetHeight();

	if (bx2 <= x1 || bx1 >= x2 || by2 <= y1 || by1 >= y2) {
		return false;
	}
	return true;
}

LinkedList<Body> Body::AllColisions () {
	LinkedList<Body> ans;
	Body tmp;
	Objects.ResetPull();
	tmp = Objects.Pull();
	while (tmp != NULL) {
		if (Collide(tmp)) {
			ans.Add(tmp);
		}
		tmp = Objects.Pull();
	}
	return ans;
}

int Body::CollideNormal (Body b) {
	if (!Collide(b)) {
		return -1;
	}
	if (GetFX() > b.GetFX() + b.GetWidth() - 1) {
		return 2;
	}
	if (GetFX() + GetWidth() < b.GetFX() + 1) {
		return 0;
	}
	if (GetFY() > b.GetFY() + b.GetHeight() - 1) {
		return 3;
	}
	return 1;
}

void Body::Update () {
	if (solid) {
		LinkedList ll = AllColisions();
		if (ll.Lenght() != 0) {
			int normal = CollideNormal(ll.Get(0));
			if (normal == 0 || normal == 2) {
				SetVelocity(-GetVelX(), GetVelY());
				ll.Get(0).SetVelocity(-ll.Get(0).GetVelX(), ll.Get(0).GetVelY());
			} else {
				SetVelocity(GetVelX(), -GetVelY());
				ll.Get(0).SetVelocity(ll.Get(0).GetVelX(), -ll.Get(0).GetVelY());
			}
		}
	}
	if (!stationary) {
		SetPosition(GetFX() + GetVelX(), GetFY() + GetVelY());
	}
	Draw ();
}

void Body::Draw () {
	window.~Window();
	Window w(width, height, x, y, ch);
	w.setCouleurBordure(color);
	w.setCouleurFenetre(color);
	window = w;
}
