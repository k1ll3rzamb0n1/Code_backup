#include "monster.h"
#include "player.h"
#include <ctime>
#include <windows.h>

// Monster location class

//constructor
Monster::Monster(bool f, bool p, bool m, bool g, bool grail, int h, int a):Location(f,p,m,g,grail)
{
	health = h;
	attack = a;
}

// accessors and mutators
int Monster::getAttack()
{
	return attack;
}
void Monster::setAttack(int a)
{
	attack = a;
}
int Monster::getHealth()
{
	return health;
}
void Monster::setHealth(int h)
{
	health = h;
}

//special for the fight
void Monster::printFight(int playershealth, int orkshealth, int pdamage, int odamage)
{
	system("cls");

	cout << "Your Health: " << playershealth << " \nDamage you did: " << pdamage << "\nRemaining Enemy Health: " << orkshealth << "\nDamage ork did to you: " << odamage << endl;
	if (orkshealth < 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "Victory is yours!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	system("PAUSE");
}
// does the actul fight and calls the print function
int Monster::fightSequence(int damage1,int hP, int& h, int a)
{
	// ok so heres how the fight goes
	// first the players damage for this turn will be his attack power plus some number one through ten. to randomize damage done 
	// then the player health is set to be ph
	// the monsters damage is some randum number between one and his attack power
	// the health of the monster will be his current health minus the damage the player does. and if its health is still greater than 0 he will hurt the player by the amoutnt that is stored in oa
	int damage = damage1 + rand() %10;
	int oa = rand() %a +1;
	h = h - damage;
	if(h > 0)
	{
		hP = hP-oa;
	}
	// after the actual fight occurs will print some message of the outcome and what happens.
	printFight(hP,h,damage,oa);
	return hP;
}

// comes from locations virtual function - does the fight sequence
void Monster::runEvent(Player& user)
{
	system("cls");
	srand((unsigned)time(0));
	int choice;
	bool run = false;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "You have stumbled upon a wild Ork! " << endl; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	do
	{
	cout << "What would you like to do?\n1) Attack\n2)Run " << endl;
	cin >> choice;
	
	switch(choice)
	{
	case 1:
		int playerhp;
		playerhp = fightSequence(user.getAttackPower(),user.getHP(),health,attack);
		user.setHP(playerhp);
		break;
	case 2:
		run = true;
		break;
	default:
		break;
	}

	}while(!run && user.getHP() > 0 && health > 0);

	if (run == true)
	{
		cout << "\nyou ran away\n";
	}
	else if(user.getHP() <= 0)
	{
		cout << "\nYou Died!!\n";
		user.die();
	}
	else if(health <= 0)
	{
		cout << "You win!!";
		if(getVisited() == false)
		{
			user.addClue();
			cout << "\n You gained a clue!" << endl;
		}
	}
	system("PAUSE");
}
