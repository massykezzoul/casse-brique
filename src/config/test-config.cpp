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
		g++ test-config.cpp config.cpp ../raquette.cpp ../ball.cpp ../window.cpp convert/convert.cpp ../brick.cpp ../player.cpp ../level.cpp -o conf -lncurses
*/

int main(int argc, char** argv){

	Config conf(CONFIG_FILE);

	cout << "Ball" << endl;

	cout << "\tChar : " << conf.get_ball().get_char() << endl
		<< "\tspeed : " << conf.get_ball().get_speed() << endl
		<< "\tangle : " << conf.get_ball().get_angle() << endl;

	cout << "Bat" << endl;

	cout << "\tChar : " << conf.get_raquette().get_char() << endl
		<< "\tspeed : " << conf.get_raquette().get_speed() << endl
		<< "\ttaille : " << conf.get_raquette().get_width() << endl;

	for (int i = 0 ; i < conf.get_size() ; i++ ) {
		cout << "Level" << endl;

		cout << "\tNbbricks * NbLines : " << conf.get_level(i).get_bricks().get_size() << endl;

	}

return 0;
}

