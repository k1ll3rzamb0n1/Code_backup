// high low guessing game

#include <ctime>
#include <iostream>
#include "highlow.h"
#include <windows.h>

using namespace std;
//constructor
Highlow::Highlow(bool v, bool p, bool m, bool g, bool grail):Location(v,p,m,g, grail)
	{
		srand((unsigned) time(0));
		guessMe = rand() % 10 + 1;
	}

	//accesor/mutator

int Highlow::getguessMe()
	{
		return guessMe;
	}
void Highlow::setguessMe(int i)
{
	guessMe = i;
}
	
	
	// the game
void Highlow::runEvent(Player& user)
{
	system("cls");
	cout << "Welcome to the game of Highlow!\n";
	int counter = 0;
	int guess;
	bool win = false;
	do
	{
	cout << "\nChoose a number 1 - 10 :";
	cin >> guess;
	cout << endl;
	if ( guess == guessMe)
	{
		cout << "You have defeated my superior intellect!\n";
		win = true;
	}
	if ( guess < guessMe)
	{
		cout << "You guess too low little knight\n";
	}
	if ( guess > guessMe)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << "You guessed too high, mwahahaha\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	counter++;

	}while(counter < 4 && !win);
	
	if (win = true)
	{
		user.addHP(20);
		cout << "\nYou got a health bonus\n";
	}
	else
	{
		user.subractHP();
	}
	cout << endl << "Your health now" << user.getHP() << endl;

	system("PAUSE");

}