//Game Class
#include <iostream>
#include <fstream>
#include <string>

#include "location.h"
#include "player.h"

using namespace std;


#ifndef GAME_H
#define GAME_H

class Game
{
private:
	Location*** grid;
	Player p1;
	int rows, cols;
	int prow, pcol;
public:
	// constructor
	Game();
	// plays the game at location
	bool play();
	//prints grid
	void printg(Player you);
};
#endif