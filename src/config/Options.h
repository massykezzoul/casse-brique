#ifndef __OPTIONS
#define __OPTIONS

#include<string.h>

class Option{
public:
	enum Type{
		HELP,
		VERSION,
		AUTHORS,
		NOTYPE
	};
private:
	Type type;
	std::string description;
public:
	Option();
  	Option(Type type,std::string description);
	//getters
	Type GetType()const;
	std::string GetDescription()const;
	//setters
	void SetType(Type optiontype);
	void SetDescription(std::string s);
	//methods
	void PassOption(std::string s);
	void PrintOptions();
};

#endif 