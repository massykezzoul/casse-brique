#include <iostream>

#include "window.h"
#include "LinkedList.h"
#include "Body.h"
#include "GameBoard.h"

using namespace std;

GameBoard::GameBoard(){
	Body::Body MenuWindow(30,5,10,10,WRED,' ',true,true,w);
	Body::Body GameWindow(5,5,20,20,BWHITE,' ',true,true,w);
	//Window* Frame = new Window(30, 50, 1, 1, '+');
} 

