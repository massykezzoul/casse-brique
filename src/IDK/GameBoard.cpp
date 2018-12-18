#include <iostream>

#include "window.h"
#include "LinkedList.h"
#include "Body.h"
#include "GameBoard.h"

using namespace std;

GameBoard::GameBoard(){
	Body MenuWindow=mw(5, 5, 1, 40, WRED, ' ', true, true, w);
	Body GameWindow=gw(5, 5, 20, 1, WRED, ' ', true, true, w);
	//Window* Frame = new Window(30, 50, 1, 1, '+');
} 