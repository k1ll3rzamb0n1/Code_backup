#include "game.h"
#include "monster.h"
#include "highlow.h"
#include "movegame.h"
#include "location.h"
#include "player.h"
#include "holygrail.h"

#include <iostream>
#include <windows.h>
#include <string>

// constructor - makes the game sets the player defaults    creates the grid and assignes all the spaces read in from file
Game::Game()
{
	string name;
	cout << "What is your name sir knight? :";
	cin >> name;

	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 484);
	cout << "\nVery good ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 482);
	cout << name;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 484);
	cout << " your quest awaits" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	p1.setName(name);

	system("PAUSE");

	char temp;

	ifstream in;
	in.open("file.txt");
	
	in >> rows >> cols;

	grid = new Location**[rows];
	
	for(int i = 0; i < rows; i++)
	{
		grid[i] = new Location*[cols];
	}


	for(int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			in >> temp;
			if( temp == 'e')
			{
				grid[r][c] = new Location(false, false, false, false, false);
			}
			else if( temp == 'g')
			{
				grid[r][c] = new Holygrail(false, false, false, false, true);
			}
			else if( temp == 'm')
			{
				grid[r][c] = new Monster(false, false, true, false, false, 30,15);
			}
			else if( temp == 'h')
			{
				grid[r][c] = new Highlow(false, false, false, true, false);
			}
			else if( temp == 'v')
			{
				grid[r][c] = new Movegame(false, false, false, true, false);
			}
			else if( temp == 'P')
			{
				grid[r][c] = new Location(true, true, false, false, false);
				prow = r;
				pcol = c;
			}
		}
	}
}

// will display the game board to my spesifications:  will create the tree and river look but will replace that with the locations type after the space has been visited
void Game::printg(Player you)
{

	system("cls");

	if(you.getClues() >= 5)
	{
		cout << "The grail in which you seek lies in a secluded patch of forest. Accross the river wide and far to the east of the land." << endl << endl;
	}
	else
	{
		cout << "Your mission is to search for the holy grail. BUT first you must find the clues to its location. 5 to be exact. These mistical clues are guarded by monsters    accross the map. good luck.\n\n";
	}
	for(int rw = 0; rw < rows; rw++)
	{
		for(int cl = 0; cl < cols; cl++)
		{
			
			if(grid[rw][cl]->getHoldPlayer() == true)
			{
				cout << "[";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				cout << "P";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "]";
			}
			else if(grid[rw][cl]->getIsMonster() == true && grid[rw][cl]->getVisited() == true)
			{
				cout << "[";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "M";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "]";
			}
			else if(grid[rw][cl]->getIsPuzzle() == true && grid[rw][cl]->getVisited() == true)
			{
				cout << "[";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << "R";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "]";
			}
			else
			{
				
				if((rw > 5 && cl > 3) || (rw < 3 && cl < 7 && cl > 3) || (rw == 1 && cl == 3) ||(rw == 3 && cl == 5) || (rw == 4 && cl == 7) || (rw == 4 && cl < 3) || ((rw == 3 || rw == 5) && cl == 1))
				{
					cout << "[";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
					cout << "^";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "]";
				}
				else if((rw ==2 && cl == 7) || (rw == 3 && cl > 5) || (rw == 4 && (cl == 4 || cl == 5 || cl == 6)) || ( rw == 5 && (cl == 3 || cl == 4 || cl == 5)) || ( rw == 6 && (cl == 3 || cl == 2)) || (rw == 7 && (cl == 2 || cl == 1 || cl == 3)))
				{
					cout << "[";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
					cout << "/";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "]";
				}
				else
				cout << "[ ]";
			}
		}
		cout << endl;
	}
}

// plays the game, tests spots and will return when the player wins or loses
// play game will move the player around the board testing if they are on an edge and will call the run event function at each space that they land
//if the players health reaches 0 then it ends with a lose condition, if the player finds the holy grail than it returns a win
bool Game::play()
{
	bool win = false, lose = false;
	char direction;
	bool valid = false;

	do
	{

		printg(p1);

			do
			{
				
				cout << "which way would u like to move? <w,a,s,d controls>: ";
				cin >> direction;
				valid = true;

			if(direction == 'w' || direction == 'W')
			{
				if (prow == 0)
				{
					valid = false;
				}
				else
				{
					grid[prow][pcol]->setHoldsPlayer(false);
					prow--;
					grid[prow][pcol]->setHoldsPlayer(true);
				}
			}
			else if(direction == 'd' || direction == 'D')
			{
				if (pcol == cols-1)
				{

					valid = false;
	
				}
				else
				{
					grid[prow][pcol]->setHoldsPlayer(false);
					pcol++;
					grid[prow][pcol]->setHoldsPlayer(true);
				}
			}
			else if(direction == 's' || direction == 'S')
			{
				if (prow == rows-1)
				{
					valid = false;
				}
				else
				{
					grid[prow][pcol]->setHoldsPlayer(false);
					prow++;
					grid[prow][pcol]->setHoldsPlayer(true);
			
				}
			}
			else if(direction == 'a' || direction == 'A')
			{
				if (pcol == 0)
				{
					valid = false;
				}
				else
				{
					grid[prow][pcol]->setHoldsPlayer(false);
					pcol--;
					grid[prow][pcol]->setHoldsPlayer(true);
				}
			}
			if(valid == false)
			{
				cout << "invalid move";
			}
			}while(valid == false);
		
			if(grid[prow][pcol]->getVisited() == false || grid[prow][pcol]->getGrail() == true)
			{
			grid[prow][pcol]->runEvent(p1);
			}

		grid[prow][pcol]->setVisited(true);


		if(p1.getHolyGrail() == true)
		{
			win = true;
		}
		if(p1.getDead() == true)
		{
			lose = true;
		}
	}while(win == false && lose == false);

	if(win = true)
	{
		return true;
	}
	else
		return false;
	
}