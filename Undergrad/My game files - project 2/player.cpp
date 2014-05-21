#include "player.h"
#include <string>

//Player class

//Constructors
	Player::Player()
	{
	name = "The Nameless Knight";
	HP = 100;
	clues = 0;
	attackPower = 10;
	dead = false;
	holygrail = false;
	}
	Player::Player(string n, int hp, int clue, int pow)
	{
		name = n;
		HP = hp;
		clues = clue;
		attackPower = pow;
		dead = false;
		holygrail = false;
	}

	//accessors
	string Player::getName()
	{
		return name;
	}
	int Player::getHP()
	{
		return HP;
	}
	int Player::getClues()
	{
		return clues;
	}
	int Player::getAttackPower()
	{
		return attackPower;
	}
	bool Player::getDead()
	{
		return dead;
	}
	bool Player::getHolyGrail()
	{
		return holygrail;
	}

	// mutators
	void Player::setName(string n)
	{
		name = n;
	}
	void Player::setHP(int hp)
	{
		HP = hp;
	}
	void Player::setClues(int c)
	{
		clues = c;
	}
	void Player::setAttackPower(int a)
	{
		attackPower = a;
	}
	void Player::addClue()
	{
		clues++;
	}
	void Player::subtractClue()
	{
		clues--;
	}
	void Player::addHP(int h)
	{
		HP = HP + h;
	}
	void Player::subractHP()
	{
		HP--;
	}
	void Player::die()
	{
		dead = true;
	}
	void Player::holyG()
	{
		holygrail = true;
	}