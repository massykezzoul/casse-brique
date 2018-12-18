#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "config.h"
using namespace std;



// Cleans the line of comments
void clean_line(string &s){
  size_t pos=s.find_first_of("#");
  s=s.substr(0,pos);  
  int beg=0,end=s.size()-1;
  while(beg<end+1 && (s[beg]==' ' || s[beg]=='\t' )) beg++;
  while(end>beg-1 && (s[end]==' ' || s[beg]=='\t' )) end--;
  s=s.substr(beg,end-beg+1);
}

//Separates the key from the value
bool findKeyValue(std::string &s, std::string &s1,std::string &s2){
  clean_line(s);
  if (s==string("")) return false;
  size_t pos=s.find_first_of(":");
  if (pos==string::npos) {
    cerr << "File is badly formatted" << endl;
    terminate();
  }
  s1=s.substr(0,pos);
  s2=s.substr(pos+1);
  clean_line(s1);
  clean_line(s2);
  cerr<<"Found key/value -> "<< s1<< " and "<<s2<<endl;
  return true;
}

//Passes the Values to the game
/*void Game::Option(const string &key, const string &value){
  if (key == "Shape") {
    //
  }
  if (key == "Durability") {
    //
  }
  if (key == "BoardSize") {
    size_t x, y;
    size_t pos = value.find_first_of("x");
    x = atoi(value.substr(0, pos).c_str());
    y = atoi(value.substr(pos).c_str());
    //    
  }
}*/
  
