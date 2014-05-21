#include "location.h"
#include "game.h"

#ifndef HOLYGRAIL_H
#define HOLYGRAIL_H
class Holygrail: public Location
{
public:
	Holygrail(bool f, bool p, bool m, bool g, bool grail);
	void runEvent(Player& you);
};
#endif

