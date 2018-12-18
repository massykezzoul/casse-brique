#include "Options.h"
#include "string.h"

using namespace std;

Options::Option():type(NOTYPE),description(){};
Options::Option(Type type,string description):type(type),description(description){};

Type Options::GetType()const{ return type; }
string Options::GetDescription()const{ return description;}

void Options::SetType(Type optiontype){type=optiontype;}
void Options::SetDescription(string s){description=s;}

void Options::PassOption(string s){
	if(s=='-help'){
		SetDescription("This option gives help to the palyer");
		SetType(HELP);
	}
}

void Options::PrintOption(){
	cout<<type<<" : "<<description<<endl;
}
