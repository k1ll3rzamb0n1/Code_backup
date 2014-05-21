#include "InterAct2D.h"

/*****************************************************************************
 *  Useful Drawing Functions
 ****************************************************************************/
/* centerScreen
 * Description: Returns the center of the window
 */
Point centerScreen(Event e)
{
	double center_x = e.screen_width/2.0;
	double center_y = e.screen_height/2.0;
	return Point(center_x,center_y);
}
/* clearScreen
 * Description: Clears the window and sets the background to color c
 */
void clearScreen(Event e, Color c)
{
	// draws rectangle as large as the whole screen
	Rect background(centerScreen(e), e.screen_width, e.screen_height);
	background.setFillColor(c);
	background.setOutlineColor(c);
	background.draw();
}

/*****************************************************************************
 *  Board Class Declaration
 ****************************************************************************/
class Board
{
private:
	char board [6][7];
	void printColNum(double x, double y, string num);
public:
	Board();
	void getArray(char theArray[][7]);
	void printBoard(Event e);
	bool checkMove(int col);
	void makeMove(char player, int col, Event e);
	void undoMove(int col);
	bool isFull();
	void reset();
	bool hasWon(char player);
};

/*****************************************************************************
 *  PlayerX Class Declaration and Definitions
 ****************************************************************************/

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



/*****************************************************************************
 *  PlayerO Class Declaration and Definitions
 ****************************************************************************/


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



/*****************************************************************************
 *  Board Function Definitions
 ****************************************************************************/

/* Board()
 * Description: Initializes the connect 4 board to be empty (as denoted by 'e')
 */
Board::Board()
{
	// for every row and column pair fill in an 'e'
	for (int row = 0; row < 6; row++)
		for (int col = 0; col < 7; col++)
			board[row][col] = 'e';
}
/* getArray
 * Description: Fill the parameter theArray with the values currently stored in the
 *              game board.
 */
void Board::getArray(char theArray[][7])
{
	for (int row = 0; row < 6; row++)
		for (int col = 0; col < 7; col++)
			theArray[row][col] = board[row][col];
}
/* printBoard()
 * Description: Draws the game board onto the screen
 */
void Board::printBoard(Event e)
{
	// clear off existing images
	clearScreen(e, white);

	// calculate size of each cell
	double colWidth = e.screen_width / 9.0;
	double rowWidth = e.screen_height / 8.0;
	double size = colWidth;
	if (colWidth > rowWidth)
		size = rowWidth;

	// print reminder of who plays red and blue
	Text t (Point(4.5*size, 0.5*size), " PlayerX plays Red and PlayerO plays Blue ");
	t.setOutlineColor(teal);
	t.setFillColor(white);
	t.draw();

	// draw the lines that divide the columns
	for (int c = 1; c <= 8; c++)
	{
		Line l(Point(c*size,size),Point(c*size,7*size));
		l.setFillColor(black);
		l.draw();
	}
	// draw the bottom line and column numbers
	Line l(Point(size,7*size),Point(8*size,7*size));
	l.setFillColor(black);
	l.draw();
	printColNum(1.5*size,7.5*size,"0");
	printColNum(2.5*size,7.5*size,"1");
	printColNum(3.5*size,7.5*size,"2");
	printColNum(4.5*size,7.5*size,"3");
	printColNum(5.5*size,7.5*size,"4");
	printColNum(6.5*size,7.5*size,"5");
	printColNum(7.5*size,7.5*size,"6");

	// for each cell, if there's an X there, print a red token, 
	// if there's an O there, print a blue token.
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 7; col++)
		{
			if (board[row][col] == 'X')
			{
				// find center of cell
				double centerX = (col+1.5)*size;
				double centerY = (row+1.5)*size;
				// create and print red circle
				Oval token (Point(centerX,centerY),size-0.5,size-0.5);
				token.setFillColor(red);
				token.setOutlineColor(red);
				token.draw();
			}
			else if (board[row][col] == 'O')
			{
				// find center of cell
				double centerX = (col+1.5)*size;
				double centerY = (row+1.5)*size;
				// create and print blue circle
				Oval token (Point(centerX,centerY),size-0.5,size-0.5);
				token.setFillColor(blue);
				token.setOutlineColor(blue);
				token.draw();
			}
		}
	}
}
/* printColNum
 * Description: prints out a column number for the grid
 *              called by printBoard
 */
void Board::printColNum(double x, double y, string num)
{
	Text t (Point(x,y), num);
	t.setOutlineColor(black);
	t.setFillColor(white);
	t.draw();	
}
/* checkMove()
 * Description: Tests to see if the proposed move is legal
 */
bool Board::checkMove(int col)
{
	// if outside of legal column values, return false
	if (col < 0 || col > 6)
		return false;
	// if column is full, return false
	if (board[0][col] != 'e')
		return false;
	// otherwise, it's ok
	return true;
}
/* makeMove()
 * Description: If the move is legal, updates the game board to reflect the
 *              move the player is making.
 */
void Board::makeMove(char player, int col, Event e)
{
	// Test for legality
	if (checkMove(col))
	{
		// Find lowest empty row in specified column
		for (int i = 5; i >= 0; i--)
			if (board[i][col] == 'e')
			{
				// Fill in player's move
				board[i][col] = player;
				return;
			}
	}
}
/* undoMove
 * Description: Removes the last token placed in the specified column
 */
void Board::undoMove(int col)
{
	for (int row = 0; row < 6; row++)
	{
		if (board[row][col] != 'e')
		{
			board[row][col] = 'e';
			return;
		}
	}
}
/* isFull()
 * Description: Tests to see if board is completely full by checking top of each column
 */
bool Board::isFull()
{
	bool full = true;
	// since fill from bottom (row 5), just test row 0 for each column
	for (int col = 0; col < 7; col++)
		if (board[0][col] == 'e')
			full = false;
	return full;
}
/* reset()
 * Description: Resets the board to be full of e's
 */
void Board::reset()
{
	// for every row and column pair fill in an 'e'
	for (int row = 0; row < 6; row++)
		for (int col = 0; col < 7; col++)
			board[row][col] = 'e';
}
/* hasWon
 * Description: Tests to see if the specified player has won the game by checking all
 *              4-in-a-row, 4-in-a-column and 4-on-a-diagonal possibilities.
 */
bool Board::hasWon(char player)
{
	// test for 4 in a row
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (board[row][col] == player &&
				board[row][col+1] == player &&
				board[row][col+2] == player &&
				board[row][col+3] == player)
				return true;
		}
	}
	// test for 4 in a column
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 7; col++)
		{
			if (board[row][col] == player &&
				board[row+1][col] == player &&
				board[row+2][col] == player &&
				board[row+3][col] == player)
				return true;
		}
	}
	// test for up-right diagonals
	for (int row = 5; row > 2; row--)
	{
		for (int col = 0; col < 4; col++)
		{
			if (board[row][col] == player &&
				board[row-1][col+1] == player &&
				board[row-2][col+2] == player &&
				board[row-3][col+3] == player)
				return true;
		}
	}
	// test for up-left diagonals
	for (int row = 5; row > 2; row--)
	{
		for (int col = 6; col > 2; col--)
		{
			if (board[row][col] == player &&
				board[row-1][col-1] == player &&
				board[row-2][col-2] == player &&
				board[row-3][col-3] == player)
				return true;
		}
	}

	// else, hasn't won
	return false;
}

/*****************************************************************************
 *  Global State Variable Declarations
 ****************************************************************************/
Board b;
PlayerX px('X');
PlayerO po('O');
double elapsed;
char lastPlayer;
bool gameOver;
bool started;

/* handleEvent
 * Description: Responds to events and is main entry point into the program
 */
void handleEvent(Event event)
{
	// if hit restart, reset the board and ask who has the first turn
	if (event.restart)
	{
		// seed random number generator in case anyone uses it
		srand((unsigned)time(0));
		// reset elapsed time and flag game as not yet started
		elapsed = 0.0;
		started = false;
		// clear the board and flag game as not yet finished
		b.reset();
		gameOver = false;
		// Prompt user to enter which player will go first
		clearScreen(event,white);
		Text round (centerScreen(event), " Please Type Which Player Will Have The First Turn (X or O) ");
		round.setOutlineColor(teal);
		round.setFillColor(white);
		round.draw();
	}
	// if the game hasn't yet started, check which key has been pressed to select which player goes first
	if (!started && event.key_typed)
	{
		// if X is going first, initialize lastPlayer variable to O,
		// so that it is X's turn next, and vice versa
		if(event.key == 'o' || event.key == 'O')
			lastPlayer = 'X';
		else
			lastPlayer = 'O';
		// reset the clock and flag the game as started
		elapsed = 0.0;
		started = true;
		// print message indicating who plays which colour
		clearScreen(event, white);
		Text splash (centerScreen(event), " PlayerX plays Red and PlayerO plays Blue ");
		splash.setOutlineColor(teal);
		splash.setFillColor(white);
		splash.draw();	
	}
	// if the game is underway, respond to the timer events that occur every 30ms.
	if (started && event.elapsed_time_msec > 0.0)
	{
		// update total elapsed time
		elapsed += event.elapsed_time_msec / 1000.0;
		// after user has had 2 seconds to read which player plays Red and Blue, print blank board
		if (elapsed > 2.0 && elapsed < 2.5)
			b.printBoard(event);
		// if the game is underway and it's X's turn, play X's move.
		if (elapsed > 2.5 && !gameOver && lastPlayer == 'O')
		{
			// Player A makes a move.
			b.makeMove('X',px.evalAllMoves(b),event);
			// updates who took the last move
			lastPlayer = 'X';
			// prints the new board state
			b.printBoard(event);
			// reset timer to allow the user 0.5 seconds to see the move before
			// next move takes place
			elapsed = 2.0;
		}
		// if the game is underway and it's O's turn, play O's move.
		if (elapsed > 2.5 && !gameOver && lastPlayer == 'X')
		{
			// Player B makes a move.
			b.makeMove('O',po.evalAllMoves(b),event);
			// updates who took the last turn
			lastPlayer = 'O';
			// prints the resulting board
			b.printBoard(event);
			// reset timer to allow user to see the move before another one occurs
			elapsed = 2.0;
		}

		// check to see if A has won
		if (b.hasWon('X'))
		{
			// it's end of current game
			gameOver = true;
			// print result
			Text xWin (centerScreen(event), "Congratulations PlayerX, you have won!!");
			xWin.setOutlineColor(green);
			xWin.setFillColor(white);
			xWin.draw();	
		}
		// check to see if B has won
		if (b.hasWon('O'))
		{
			// it's end of current game
			gameOver = true;
			// print result
			Text oWin (centerScreen(event), "Congratulations PlayerO, you have won!!");
			oWin.setOutlineColor(green);
			oWin.setFillColor(white);
			oWin.draw();	
		}
		// check to see if it's a stalemate
		if (b.isFull())
		{
			// it's end of current game
			gameOver = true;
			// print result
			Text stale (centerScreen(event), "A Stalemate!  Too Bad!");
			stale.setOutlineColor(red);
			stale.setFillColor(white);
			stale.draw();	
		}

	}
}