# include <iostream>
# include <ctime>
using namespace std;

void printBoard (char board[][3])
{
	for (int a = 0; a < 3; a++)
	{
		for(int b = 0; b < 3; b++)
		{
			cout << board[a][b] << " ";
		}
		cout << endl;
	}
}

bool isFilled (char board[][3],int a, int b)
{
if (board [a][b] != 'e')
	return true;
else
return false;
}

char 1stplayer ()
{
	int firstplayer = rand()%2 + 1
		if (firstplayer == 1)
			return 'X';
		else
			return 'O';
}
char player (char lastplayer)
{
	if (lastplayer == 'O')
		return 'X';
	else
		return 'O';
}

void move(char board[][3],char player)

int main ()
{
	srand ((unsigned)time(0));
	char grid [3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int x = 0; x <3; x++)
		{
		grid[i][x] = 'e';
		}
	}
	printBoard(grid);
char turn = firstplayer ();
int row;
int col;
move (grid,turn);
turn = player();


cout << "what row and col do u want to check?";
cin >> row >> col;

bool checker = isFilled (grid, row, col);

//    if (checker == true)
//    cout << "filled\n";
//	  if (checker == false)
//	  cout << "empty\n";


	system ("PAUSE");

}
