#include "location.h"

class Highlow:public Location
{
private:
	int guessMe;
	bool isPuzzle;

public:
	//constructor
	Highlow(bool v, bool p, bool m, bool g, bool grail);
	//accesor/mutator
	bool getyouGotIt();
	void setyouGotIt(bool y);
	int getguessMe();
	void setguessMe(int i);
	// the game
	void runEvent(Player& user);
};
