#include <iostream>
#include <string>
#include <fstream>
#include "config.h"
using namespace std;


int main(int argc, char** argv){
	string line;
	string key,value;
	ifstream file;
	file.open("config.cfg");
	if(!file.is_open()){
		cout<<"Error in opening config file"<<endl;
	}
	while(!file.eof()){
		getline(file,line,'\n');
		cout<<line<<endl;;
		findKeyValue(line,key,value);
	}
	file.close();
return 0;
}

