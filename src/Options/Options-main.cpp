#include <iostream>
#include "Options.h"

using namespace std;

int main(int argc, char** argv){
	string s=argv[1];
	Option O();
	O.PassOption(s);
	O.PrintOption();
	return 0;
}