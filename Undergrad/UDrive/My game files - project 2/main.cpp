// This is my game  - Ryan Bleile -


#include "location.h"
#include "player.h"
#include "game.h"

#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

// Title screen - and into
void printIntro()
{
	system("title QUEST");
	system("color 20");
	system("color 30");
	system("color 40");
	system("color 07");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 480);
	cout << "                              \nWelcome to the game of Quest!!\n                              ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << endl;
	system("PAUSE");
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "Youe have entered a time when the one with the biggest sword \nis the strongest, \nand the one with the Holy Grail rules them all. \nThis is a time of mythical creatures and great battles.\nOf life threatning puzzles and no one to help you\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << endl << "ARE YOU GAME!!"<<endl;
	system("PAUSE");
}

void winningLine()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "YOU HAVE WON!!\nThe Holy Grail is yours!\nNow you can use its power to rule the land.\nWell done sir knight, u have done well.";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	system("color 20");
	system("color 30");
	system("color 40");
	system("color 50");
	system("color 07");
}
void loosingLine()
{
	system("cls");
	cout << "Nooo... you have died in your quest to reach the Holy Grail.\nIde say better luck nxt time but...\nWell yur dead. so sory bout that.\n and i really thougt you could do it too.\n well enjoy the after life!\nMwahahahahaha!!!";
	system("color 04");
	system("color 40");
	system("color 04");
	system("color 40");
	system("color 04");
	system("color 07");
}

int main()
{
	printIntro();

	Game letsPlay;
bool won = false;
	won = letsPlay.play();
	if (won = true)
	{
		winningLine();
	}
	else
	{
		loosingLine();
	}
	cout << endl;
	system ("PAUSE");
}

