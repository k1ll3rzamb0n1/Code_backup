#include "location.h"

// Location Function Definitions

//constructors
Location::Location()
{
	visited = false;
	holdsPlayer = false;
}
Location::Location(bool b, bool p, bool m, bool g, bool grail)
{
	visited = b;
	holdsPlayer = p;
	impediment = false;
	isMonster = m;
	isPuzzle = g;
	isGrail = grail;

}

// Mutators and accessors
bool Location::getHoldPlayer()
{
	return holdsPlayer;
}
void Location::setHoldsPlayer(bool h)
{
	holdsPlayer = h;
}
bool Location::getVisited()
{
	return visited;
}
void Location::setVisited(bool v)
{
	visited = v;
}
bool Location::getImpediment()
{
	return impediment;
}
void Location::setImpediment(bool I)
{
	impediment = I;
}
bool Location::getIsMonster()
{
	return isMonster;
}
bool Location::getIsPuzzle()
{
	return isPuzzle;
}
void Location::setIsMonster()
{
	isMonster = true;
}
void Location::setIsPuzzle()
{
	isPuzzle = true;
}
bool Location::getGrail()
{
	return isGrail;
}
// the virtual run function
void Location::runEvent(Player& user)
{
	return;
}