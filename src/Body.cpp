// Author : Romain Fournier romain.fournier.095@gmail.com
#include "Body.h"
#include "window.h"

Body::Body(int x, int y, int height, int width, Color color, char ch=' '): x((float)x), y((float)y), width(width), height(height), velX(0), velY(0), color(color) {
	if (AllColisions().Lenght() != 0) {//This object overlaps with something
		//TODO, Also remove the parent instance
		~Body();
	}
	Window tmp(height, width, x, y, ch);
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            