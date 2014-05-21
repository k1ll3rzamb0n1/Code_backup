#include "movegame.h"
#include "player.h"
#include <iostream>

// constructor
Movegame::Movegame(bool v, bool p, bool m, bool g, bool grail):Location(v,p,m,g, grail)
	{
		char temp;
		
		ifstream ins;
		ins.open("movegame.txt");
		
		ins >> row >> col;

		field = new Location**[row];
	
	for(int i = 0; i < row; i++)
	{
		field[i] = new Location*[col];
	}

	for(int r = 0; r < row; r++)
	{
		for (int c = 0; c< col; c++)
		{
			ins >> temp;
			if (temp == 'e')
			{
				field[r][c] = new Location(false, false, false, false, false);
			}
			else if(temp == 'p')
			{
				field[r][c] = new Location(false, true, false ,false, false);
				plcol = c;
				plrow = r;
			}
			else if(temp == 'i')
			{
				field[r][c] = new Location(false, false, false, false, false);
				field[r][c]->setImpediment(true);
			}
		}
	}
	}


//prints field game
void Movegame::printfield()
{
	system("cls");

	for(int rs = 0; rs < row; rs++)
	{
		for(int cs = 0; cs < col; cs++)
		{
			if(field[rs][cs]->getVisited() == true)
			{
				cout << "[X]";
			}
			else if(field[rs][cs]->getHoldPlayer() == true)
			{
				cout << "[P]";
			}
			else if(field[rs][cs]->getImpediment() == true)
			{
				cout<<"[+]";
			}
			else
				cout << "[ ]";
		}
		cout << endl;
	}
}

// from locations virtual function - 
void Movegame::runEvent(Player& user)
	{

		
		bool win = false, lose = false, valid = false;
		char direction;

		do
		{
			printfield();
			cout << "\nYou must find your way accross the field hitting every square, but each space only once.";
			
			do
			{
				cout << "\nwhich way would u like to move? <w,a,s,d controls>: ";
				cin >> direction;
				valid = true;

							
			if(direction == 'w' || direction == 'W')
			{
				if (plrow == 0)
				{
					valid = false;
				}
				else if(field[plrow-1][plcol]->getImpediment() == true)
				{
					valid = false;
				}
				else
				{
					field[plrow][plcol]->setHoldsPlayer(false);
					plrow--;
					field[plrow][plcol]->setHoldsPlayer(true);
					field[plrow+1][plcol]->setVisited(true);
				}
			}
			else if(direction == 'd' || direction == 'D')
			{
				if (plcol == col-1)
				{
					valid = false;
				}
				else if(field[plrow][plcol+1]->getImpediment() == true)
				{
					valid = false;
				}
				else
				{
					field[plrow][plcol]->setHoldsPlayer(false);
					plcol++;
					field[plrow][plcol]->setHoldsPlayer(true);
					field[plrow][plcol-1]->setVisited(true);
				}
			}
			else if(direction == 's' || direction == 'S')
			{
				if (plrow == row-1 || field[plrow+1][plcol]->getImpediment() == true)
				{
					valid = false;
				}
				else if(field[plrow+1][plcol]->getImpediment() == true)
				{
					valid = false;
				}
				else
				{
					field[plrow][plcol]->setHoldsPlayer(false);
					plrow++;
					field[plrow][plcol]->setHoldsPlayer(true);
					field[plrow-1][plcol]->setVisited(true);
			
				}
			}
			else if(direction == 'a' || direction == 'A')
			{
				if (plcol == 0 || field[plrow][plcol-1]->getImpediment() == true)
				{
					valid = false;
				}
				else if(field[plrow][plcol-1]->getImpediment() == true)
				{
					valid = false;
				}
				else
				{
					field[plrow][plcol]->setHoldsPlayer(false);
					plcol--;
					field[plrow][plcol]->setHoldsPlayer(true);
					field[plrow][plcol+1]->setVisited(true);
				}
			}
			if(valid == false)
			{
				cout << "invalid move";
			}
			}while(valid == false);
		
			if(field[plrow][plcol]->getVisited() == true)
			{
				lose = true;
			}

			win = true;
			for(int rr = 0; rr < row; rr++)
			{
				for(int cc = 0; cc < col; cc++)
				{
					if(field[rr][cc]->getVisited() == false && field[rr][cc]->getImpediment() != true)
					{
						win = false;
					}
				}
			}
		}while(!win && !lose);

		if(lose == true && win == false)
		{
			system("cls");
			cout << "YOU LOSE! HAHAHA U COULD NOT DEFEAT MY PUZZLE MADNESS! " << endl;
			user.subractHP();

		}
		if(win == true)
		{
			system("cls");
			cout << "You beat me! arg you may advance" << endl;
			user.addHP(20);
			cout << "\nYou got a health bonus\n";
		}

		cout << endl << "Your health now" << user.getHP() << endl;

		system("PAUSE");

	}
