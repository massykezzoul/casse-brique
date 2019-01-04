#include <iostream>
#include <string>
#include <fstream>
#include "../raquette.h"
#include "../ball.h"
#include "config.h"

#define CONFIG_FILE "config.cfg"

using namespace std;

/* 
	Compilation : 
		g++ config-main.cpp config.cpp ../raquette.cpp ../ball.cpp ../window.cpp convert/convert.cpp ../brick.cpp ../player.cpp -o conf -lncurses
*/

int main(int argc, char** argv){
	string line;
	string key,value;
	ifstream file;



	Config conf(CONFIG_FILE);

	cout << "Ball" << endl;

	cout << "\tChar : " << conf.get_ball().get_char() << endl
		<< "\tspeed : " << conf.get_ball().get_speed() << endl
		<< "\tangle : " << conf.get_ball().get_angle() << endl;

	cout << "Bat" << endl;

	cout << "\tChar : " << conf.get_raquette().get_char() << endl
		<< "\tspeed : " << conf.get_raquette().get_speed() << endl
		<< "\ttaille : " << conf.get_raquette().get_width() << endl;


	file.close();
return 0;
}

