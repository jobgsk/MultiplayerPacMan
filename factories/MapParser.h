#ifndef MAP_PARSER_H_
#define MAP_PARSER_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


#include <cstdlib>
#include <vector>
#include "../GameObject.h"

using namespace std;

void ParseMap(string filename);
bool ParseWall(const char *ch, float px, float pz);
bool ParseCoint(const char *ch, float px, float pz);
bool ParsePlayer(const char *ch, float px, float pz);
bool ParseEnemy(const char *ch, float px, float pz, int num);
bool ParseNode(const char *ch, float px, float pz, int num);

#endif /* MAP_PARSER_H_ */