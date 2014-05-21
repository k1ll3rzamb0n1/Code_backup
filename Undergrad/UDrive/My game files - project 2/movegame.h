#ifndef MOVEGAME_H
#define MOVEGAME_H

#include <fstream>
#include "location.h"
#include "player.h"

using namespace std;

class Movegame: public Location
{
private:
	Location*** field;
	int row, col;
	int plcol, plrow;
public:
	// constructor
	Movegame(bool v, bool p, bool m, bool g, bool grail);
	//class function - to play the game
	void runEvent(Player& user);
	void printfield();

};

#endif
