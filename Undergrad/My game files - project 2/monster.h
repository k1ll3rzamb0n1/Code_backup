

#include "player.h"
#include <iostream>

#ifndef MONSTER_H
#define MONSTER_H

#include "location.h"
using namespace std;

class Monster: public Location
{
private:
	int health;
	int attack;
public:
	// constructor
	Monster(bool f, bool p, bool m, bool g, bool grail, int h, int a);
	// accessors
	int getAttack();
	int getHealth();
	//mutators
	void setAttack(int a);
	void setHealth(int h);
	// this classes run event plus other functions that run event will use - eventually
	void runEvent(Player& user);
	int fightSequence(int damage1,int hP, int& h, int a);
	// will show the results after each round of battle
	void printFight(int playershealth, int orkshealth, int pdamage, int odamage);
};

#endif
