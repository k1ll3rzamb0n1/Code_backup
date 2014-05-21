#include "holygrail.h"

Holygrail::Holygrail(bool f, bool p, bool m, bool g, bool grail):Location(f,p,m,g,grail)
{
}
void Holygrail::runEvent(Player& you)
{
	if(you.getClues() >= 5)
	{
		you.holyG();
	}
}