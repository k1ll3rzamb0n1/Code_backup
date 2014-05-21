// Ryan Bleile
class PlayerX
{
private: 
	char playerx;
	Board b;

public:
	PlayerX();
	int evalMove(int col, char aray[][7]);
	int bestMove(int scores[], char myBoard[][7]);
	int evalAllMoves(Board b);
	int picklargest(int a, int b, int c, int d);
int checkforhorizontal(int column,char aray[][7]);
int checkforverticle(int column, char aray[][7]);
int checkDiagU(int column, char aray[][7]);
int checkDiagD(int column, char aray[][7]);
int movetester(int column, char aray[][7]);
};

PlayerX::PlayerX ()
{
playerx = 'X';
}

int PlayerX::evalAllMoves(Board b)
{
int score[7];
char boardAray [6][7];
b.getArray(boardAray);
for (int i = 0; i < 7; i++)
{
	score[i] = evalMove(i,boardAray);
}
return bestMove(score, boardAray);
}
int PlayerX::evalMove(int col, char myBoard[][7])
{
	bool check = false;
	Board c;
	c.getArray(myBoard);
	c.makeMove(playerx, col);
	check = c.hasWon(playerx);
	c.undoMove(col);
	if (check == true)
		return 100;

	int countHoriz, countVert, countDiagUp, countDiagDown;

	countHoriz = checkforhorizontal(col,myBoard);
	countVert = checkforverticle(col,myBoard);
	countDiagUp = checkDiagU(col,myBoard);
	countDiagDown = checkDiagD(col,myBoard);

	return picklargest(countHoriz,countVert,countDiagUp,countDiagDown);
}

int PlayerX::picklargest(int a, int b, int c, int d)
{
	int largest[4] = {a,b,c,d};
	int change;

	do
	{
		if(largest[0] < largest[1])
		{
			change = largest[0];
			largest[0] = largest[1];
			largest[1] = change;
		}
		if(largest[1] < largest [2])
		{
			change = largest [1];
			largest[1] = largest [2];
			largest[2] = change;
		}
		if(largest[2] < largest [3])
		{
			change = largest [2];
			largest[2] = largest [3];
			largest[3] = change;
		}
	} while (largest[0] < largest[1] || largest[1] < largest[2] || largest[2] < largest[3]);

	return largest[0];
}

int PlayerX::bestMove(int score[], char myBoard[][7])
{
	for (int i = 0; i < 7; i++)
	{
		if (score[i] = 100)
		{
			return i;
		}
	}

Board test;
test.getArray(myBoard);

int change;
int scores[7];
for(int x = 0; x<7; x++)
{
	score[x]=scores[x];
}

	do
	{
		if(scores[0] < scores[1])
		{
			change = scores[0];
			scores[0] = scores[1];
			scores[1] = change;
		}
		if(scores[1] < scores [2])
		{
			change = scores [1];
			scores[1] = scores [2];
			scores[2] = change;
		}
		if(scores[2] < scores [3])
		{
			change = scores [2];
			scores[2] = scores [3];
			scores[3] = change;
		}
		if(scores[3] < scores[4])
		{
			change = scores[3];
			scores[3] = scores[4];
			scores[4] = change;
		}
		if(scores[4] < scores [5])
		{
			change = scores [4];
			scores[4] = scores [5];
			scores[5] = change;
		}
		if(scores[5] < scores [6])
		{
			change = scores [5];
			scores[5] = scores [6];
			scores[6] = change;
		}
		
		
	} while (scores[0] < scores[1] || scores[1] < scores[2] || scores[2] < scores[3] || scores[3] < scores[4] || scores [4] < scores [5] || scores [5] < scores[6]);

for (int v = 0; v < 7; v++)
	{
		if(score[v] == scores[0])
		{
			if(test.checkMove(score[v]) == true)
			{
				return score[v];
			}
		}
	}

}



int PlayerX::movetester (int column, char aray[][7])
{
	for (int i = 5; i >= 0; i--) 
			if (aray[i][column] == 'e') 
			{   
				return i; 
			} 
}

int PlayerX::checkforhorizontal(int column, char aray[][7])
{
		int inrow = 0;
		int row = movetester(column, aray);
		for (int j = column; j<7; j++) //check horizontal
		{
			if (aray[row][j] == playerx)
			{
				inrow++;
			}
			else
				j=7;
		}
		inrow --;
		for (int jj = column; jj>=0; jj--)
		{
			if (aray[row][jj] == playerx)
			{
				inrow++;
			}
			else
				jj =-1;
		}

		return inrow;
}
int PlayerX::checkforverticle(int column, char aray[][7])
{

int inrow=0;
int row = movetester(column, aray);
for (int k = row; k<6; k++)  //check vertical  checks if last piece made a verticle win
		{
			if ( aray[k][column] == playerx)
			{
				inrow++;
			}
			else
				k = 6;
		}
		inrow --;
		for (int kk = row; kk>0; kk--)
		{
			if (aray[kk][column] == playerx)
			{
				inrow++;
			}
			else
				kk = 0;
		}
	return inrow;
}

int PlayerX::checkDiagU(int column, char aray[][7])
{
	int inrow=0;
	int row = movetester(column, aray);
	for (int w = 0; w<6; w++)  //check for diagonal up
		{
				if (aray[row-w][column+w] == playerx)
				{
					inrow++;
				}
				else
				{
					w=6;
				}
		}
		inrow--;
		for (int q = 0; q < 6; q++)
		{	
			if (aray[row+q][column-q] == playerx)
				{
					inrow++;
				}
				else
				{
					q=6;
				}
		}

	return inrow;
}
int PlayerX::checkDiagD(int column, char aray[][7])
{
	int inrow=0;
	b.getArray(aray);
	int row = movetester(column, aray);
		for (int l = 0; l<6; l++)  //check for diagonal down
		{
				if (aray[row+l][column+l] == playerx)
				{
					if(row + l == 7||column+l==8)
					{
					}
					else
					{
						inrow++;
					}
				}
				else
				{
					l=6;
				}
		}
		inrow --;
		for (int p = 0; p < 6; p++)
		{	
			if (aray[row-p][column-p] == playerx)
				{
					if (row-p==-1 || column-p==-1)
					{
					}
					else
					{
					inrow++;
					}
				}
				else
				{
					p=6;
				}
		}


	return inrow;
}


class PlayerO
{
private: 
	char playero;
	Board b;

public:
	PlayerO();
	int evalMove(int col, char aray[][7]);
	int bestMove(int scores[], char myBoard[][7]);
	int evalAllMoves(Board b);
	int picklargest(int a, int b, int c, int d);
int checkforhorizontal(int column,char aray[][7]);
int checkforverticle(int column, char aray[][7]);
int checkDiagU(int column, char aray[][7]);
int checkDiagD(int column, char aray[][7]);
int movetester(int column, char aray[][7]);
};

PlayerO::PlayerO ()
{
playero = 'O';
}

int PlayerO::evalAllMoves(Board b)
{
int score[7];
char boardAray [6][7];
b.getArray(boardAray);
for (int i = 0; i < 7; i++)
{
	score[i] = evalMove(i,boardAray);
}
return bestMove(score, boardAray);
}
int PlayerO::evalMove(int col, char myBoard[][7])
{
	bool check = false;
	Board c;
	c.getArray(myBoard);
	c.makeMove(playero, col);
	check = c.hasWon(playero);
	c.undoMove(col);
	if (check == true)
		return 100;

	int countHoriz, countVert, countDiagUp, countDiagDown;

	countHoriz = checkforhorizontal(col,myBoard);
	countVert = checkforverticle(col,myBoard);
	countDiagUp = checkDiagU(col,myBoard);
	countDiagDown = checkDiagD(col,myBoard);

	return picklargest(countHoriz,countVert,countDiagUp,countDiagDown);
}

int PlayerO::picklargest(int a, int b, int c, int d)
{
	int largest[4] = {a,b,c,d};
	int change;

	do
	{
		if(largest[0] < largest[1])
		{
			change = largest[0];
			largest[0] = largest[1];
			largest[1] = change;
		}
		if(largest[1] < largest [2])
		{
			change = largest [1];
			largest[1] = largest [2];
			largest[2] = change;
		}
		if(largest[2] < largest [3])
		{
			change = largest [2];
			largest[2] = largest [3];
			largest[3] = change;
		}
	} while (largest[0] < largest[1] || largest[1] < largest[2] || largest[2] < largest[3]);

	return largest[0];
}

int PlayerO::bestMove(int score[], char myBoard[][7])
{
	for (int i = 0; i < 7; i++)
	{
		if (score[i] = 100)
		{
			return i;
		}
	}

	Board test;
	test.getArray(myBoard);

	int change;
	int scores[7];
	for(int x = 0; x<7; x++)
	{
		score[x]=scores[x];
	}

	do
	{
		if(scores[0] < scores[1])
		{
			change = scores[0];
			scores[0] = scores[1];
			scores[1] = change;
		}
		if(scores[1] < scores [2])
		{
			change = scores [1];
			scores[1] = scores [2];
			scores[2] = change;
		}
		if(scores[2] < scores [3])
		{
			change = scores [2];
			scores[2] = scores [3];
			scores[3] = change;
		}
		if(scores[3] < scores[4])
		{
			change = scores[3];
			scores[3] = scores[4];
			scores[4] = change;
		}
		if(scores[4] < scores [5])
		{
			change = scores [4];
			scores[4] = scores [5];
			scores[5] = change;
		}
		if(scores[5] < scores [6])
		{
			change = scores [5];
			scores[5] = scores [6];
			scores[6] = change;
		}
		
		
	} while (scores[0] < scores[1] || scores[1] < scores[2] || scores[2] < scores[3] || scores[3] < scores[4] || scores [4] < scores [5] || scores [5] < scores[6]);

	for (int v = 0; v < 7; v++)
	{
		if(score[v] == scores[0])
			return score[v];
	}

	}



int PlayerO::movetester (int column, char aray[][7])
{
	for (int i = 5; i >= 0; i--) 
			if (aray[i][column] == 'e') 
			{   
				return i; 
			} 
}

int PlayerO::checkforhorizontal(int column, char aray[][7])
{
		int inrow = 0;
		int row = movetester(column, aray);
		for (int j = column; j<7; j++) //check horizontal
		{
			if (aray[row][j] == playero)
			{
				inrow++;
			}
			else
				j=7;
		}
		inrow --;
		for (int jj = column; jj>=0; jj--)
		{
			if (aray[row][jj] == playero)
			{
				inrow++;
			}
			else
				jj =-1;
		}

		return inrow;
}
int PlayerO::checkforverticle(int column, char aray[][7])
{

int inrow=0;
int row = movetester(column, aray);
for (int k = row; k<6; k++)  //check vertical  checks if last piece made a verticle win
		{
			if ( aray[k][column] == playero)
			{
				inrow++;
			}
			else
				k = 6;
		}
		inrow --;
		for (int kk = row; kk>0; kk--)
		{
			if (aray[kk][column] == playero)
			{
				inrow++;
			}
			else
				kk = 0;
		}
	return inrow;
}

int PlayerO::checkDiagU(int column, char aray[][7])
{
	int inrow=0;
	int row = movetester(column, aray);
	for (int w = 0; w<6; w++)  //check for diagonal up
		{
				if (aray[row-w][column+w] == playero)
				{
					inrow++;
				}
				else
				{
					w=6;
				}
		}
		inrow--;
		for (int q = 0; q < 6; q++)
		{	
			if (aray[row+q][column-q] == playero)
				{
					inrow++;
				}
				else
				{
					q=6;
				}
		}

	return inrow;
}
int PlayerO::checkDiagD(int column, char aray[][7])
{
	int inrow=0;
	b.getArray(aray);
	int row = movetester(column, aray);
		for (int l = 0; l<6; l++)  //check for diagonal down
		{
				if (aray[row+l][column+l] == playero)
				{
					if(row + l == 7||column+l==8)
					{
					}
					else
					{
						inrow++;
					}
				}
				else
				{
					l=6;
				}
		}
		inrow --;
		for (int p = 0; p < 6; p++)
		{	
			if (aray[row-p][column-p] == playero)
				{
					if (row-p==-1 || column-p==-1)
					{
					}
					else
					{
					inrow++;
					}
				}
				else
				{
					p=6;
				}
		}


	return inrow;
}

