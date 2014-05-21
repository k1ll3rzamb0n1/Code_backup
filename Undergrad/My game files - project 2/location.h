#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <string>
#include "player.h"

using namespace std;

class Location
{
private:
	bool visited;
	bool holdsPlayer;
	bool impediment;
protected:
	// cannot be private to be accessed in children classes
	bool isMonster;
	bool isGrail;
	bool isPuzzle;
public:
	// general constructor
	Location();
	Location(bool b, bool p, bool m, bool g, bool grail);

	// mutators and accesors
	bool getHoldPlayer();
	void setHoldsPlayer(bool p);
	bool getVisited();
	void setVisited(bool v);
	bool getImpediment();
	void setImpediment(bool I);
	bool getIsMonster();
	bool getIsPuzzle();
	bool getGrail();
	void setIsMonster();
	void setIsPuzzle();
	// my run event function to be inherited
	virtual void runEvent(Player& user);

};

#endif