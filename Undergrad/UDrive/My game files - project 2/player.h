#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player
{
private:
	string name;
	int HP;
	int clues;
	int attackPower;
	bool dead;
	bool holygrail;

public:
	// constructors
	Player();
	Player(string n, int hp, int clue, int pow);
	// accesors
	string getName();
	int getHP();
	int getClues();
	int getAttackPower();
	bool getDead();
	bool getHolyGrail();
	// mutators
	void setName(string n);
	void setHP(int hp);
	void setClues(int c);
	void setAttackPower(int a);
	void addClue();
	void subtractClue();
	void addHP(int h);
	void subractHP();
	void die();
	void holyG();

};

#endif

