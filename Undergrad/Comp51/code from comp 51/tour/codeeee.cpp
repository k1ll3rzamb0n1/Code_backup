/*****************************************************************************
 *  Filename: tournament.cpp
 *  Author: E. Bowring
 *  Description: Code for the COMP 51 Connect 4 tournament.
 ****************************************************************************/
#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
using namespace std;

/*****************************************************************************
 *  Board Class Declaration
 ****************************************************************************/
class Board
{
private:
	char board [6][7];
public:
	Board();
	void getArray(char theArray[][7]);
	void printBoard();
	bool checkMove(int col);
	void makeMove(char player, int col);
	void undoMove(int col);
	bool isFull();
	void reset();
	bool hasWon(char player);
	void hostTournament();
};

/*****************************************************************************
 *  PlayerX Class Declaration and Definitions
 ****************************************************************************/

     class PlayerX {

private:
	char player;

public:
	PlayerX();
	PlayerX(char p);
	char getPlayer();
	void setPlayer(char play);
	int bestMove(int scores[]);
	int evalMove(int col, Board b);
	int evalAllMoves(Board b);
};

//Player func definitions

/* Player(): Default to player X if not initialized when defined. */
PlayerX::PlayerX() {

	player = 'X';
}

/* Player(char p): pass in p and store it as the player. */
PlayerX::PlayerX(char p) {

	player = p;
}

/* getPlayer(): acess player */
char PlayerX::getPlayer() {

	return player;
}

/* setPlayer(char play): change player from anywhere */
void PlayerX::setPlayer(char play) {

	player = play;
}

/* bestMove(): take scores[] (filled with each possible move the Player is considering) 
	and return the integer index number for the move that the player should make (which ones scored highest) */
int PlayerX::bestMove(int scores[]) {

	int highestValue = 0;
	int highestIndex;
	bool tie = false;

	//go through scores[] and find highest value
	for (int i = 0; i < 7; i++) {

		if(scores[i] == highestValue) {
			tie = true; 
		} 
		else if (scores[i] > highestValue) {
			tie = false;
			highestValue = scores[i];
			highestIndex = i;
		}
	}

	//if theres a tie, randomize
	if (tie) {

		//while(-1 < 0) is the new while(true)
		while (-1 < 0) {

			//Autobots! Randomize!
			int r = rand()%7;
			if (scores[r] == highestValue) {
				highestIndex = r;
				break;
			}
		}
	}
	return highestIndex;
}

/* evalMoveSim(): Makes a move, scores it, and then undoes it ON THE SIMULATION BOARD. */
int PlayerX::evalMove(int col, Board b) {

	int scoreMove;

	// if the move is invalid, returns -1 (so its the lowest score)
	if (b.checkMove(col) == false) {

		return -1;
	}

	b.makeMove(player, col);

	//if player is going to win, score it at 100
	if (b.hasWon(player) == true) {

		return 100;
	}
	b.undoMove(col);

	if (player == 'X') {
	
		b.makeMove('O', col);
		if (b.hasWon('O') == true) {

			b.undoMove(col);
			return 99;
		}
		else {

			b.undoMove(col);
		}
	}
	else if (player == 'O') {

		b.makeMove('X', col);
		if (b.hasWon('X') == true) {

			b.undoMove(col);
			return 99;
		}
		else {

			b.undoMove(col);
		}
	}
	
	b.makeMove(player, col);

	//if player isnt going to win
	if (b.hasWon(player) == false) {
	
		//if player is O and X can't win on next move, neither win nor lose happens, score @ 50.
		if (player == 'O' && b.hasWon('X') == false) {

			scoreMove = 50;

			if (col >=2 && col <= 4) {

				scoreMove++;
			}
			else if (col == 1 || col == 5) {

				scoreMove += 1;
			}


			b.makeMove('X', col);

			if (b.hasWon('X') == true) {

				b.undoMove(col);
				scoreMove -= 20;
			}
			else {

				b.undoMove(col);
			}
		}
		else if (player == 'X' && b.hasWon('O') == false) {

			scoreMove = 50;

			if (col >=2 && col <= 4) {

				scoreMove += 2;
			}
			else if (col == 1 || col == 5) {

				scoreMove += 1;
			}

			b.makeMove('O', col);

			if (b.hasWon('O') == true) {

				b.undoMove(col);
				scoreMove -= 20;
			}
			else {

				b.undoMove(col);
			}
		}
		//if player is X or O and hasWon for the other player, score is 0
		else {

			scoreMove = 0;
		}
	}
	
	b.undoMove(col);
	return scoreMove;
}

/* evalAllMoves: stores the scores of moves in scores[] and returns what move should be made */
int PlayerX::evalAllMoves(Board b) {

	int scores[7];

	//score it 'n' store it
	for (int q = 0; q < 7; q++) {

		scores[q] = evalMove(q, b);
	}

	//calls bestMove and stores result in goodMove
	int goodMove = bestMove(scores);
	
	/*for (int r = 0; r < 7; r++) {

		cout << scores[r] << " ";            //AOISUDJASKUDHAKLSJDIAUSHDLKASDIUAKSJD
	}
	cout << "\n";*/
	return goodMove;
}                                                                
                                                                     
                                                                     
/*****************************************************************************
 *  PlayerX Class Declaration and Definitions
 ****************************************************************************/

// PLEASE PUT YOUR PLAYER CLASS CODE HERE.


/*****************************************************************************
 *  PlayerO Class Declaration and Definitions
 ****************************************************************************/

class PlayerO
{// awesome amazing stuff
private:
	char other;
	char player;
	int scores [7];
	int best;
public:
	PlayerO(char p); // set defults 
	int bestmove (int scores []); // tells me what move out of the all of them is the best
	int evalmove (int col, Board b);// takes one move from evalallmoves and gives them a score
	int evalAllMoves (Board b); // starts the whole preocess to decide a move
};

PlayerO::PlayerO(char p) // take p and makes it so that the player and other function will work in evalmove
{
	player = p;
	if (p == 'O')
		other = 'X';
	else 
		other = 'O';
}
int PlayerO::evalAllMoves(Board b) // starts each evalmove and returns the best move
{

	for (int i = 0; i < 7; i++)
	
		scores [i]= evalmove (i,b);
	best = bestmove (scores);
	return best;
	
}
int PlayerO::evalmove (int col, Board b) // gives the score to each move
{
	if (b.checkMove (col) == false)
		return 0;
	b.makeMove (player, col);
	if (b.hasWon (player) == true)
		return 100;
	b.makeMove (other, col);
	if (b.hasWon (other) == true)
		return 0;
	b.undoMove (col);
	if (b.hasWon (player) == false)
		return 50;	
}
int PlayerO::bestmove(int scores[])// returns the move with best score
{	
	for (int i = 0; i < 7; i++)
	{
		if (scores [i] == 100)
			return i;
	}
	
	for (int w = 0; w < 7; w++)
	{
		if (scores [w] == 50)
			return w;
	}
	for (int g = 0; g < 7; g++)
	{
		if (scores [g] == 0)
			return g;
	}
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
 * Description: Prints the board to the screen in a readable format
 */
void Board::printBoard()
{
	system("CLS");
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 7; col++)
		{
			// for each cell, print a blank space if it's empty or the player who
			// occupies that cell
			if (board[row][col] == 'e')
				cout << "|   ";
			else
				cout << "| " << board[row][col] << " ";
		}
		// break line at end of each row
		cout << "|\n";
	}
	// print column numbers at bottom
	cout << "-----------------------------\n  0   1   2   3   4   5   6\n\n";
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
void Board::makeMove(char player, int col)
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
/* hostTournament
 * Description: hosts 2 games between two computer Player objects: PlayerX and PlayerO.
 *              PlayerX moves first in the first round and PlayerO moves first in the
 *              second round.
 */
void Board::hostTournament()
{
	// Create two player objects
	PlayerX px('X');
	PlayerO po('O');

	// Round 1: X plays first
	// initialize game board and who plays X and O
	bool gameOver = false;
	int move = -1;
	// announce round and pause for user to acknowledge
	cout << "Here's round 1: PlayerX goes first!\n";
	system("PAUSE");
	printBoard();
	Sleep(500);
	do
	{
		// Player X makes a move.
		move = px.evalAllMoves(*this);
		makeMove('X',move);
		printBoard();
		Sleep(500);
		// check to see if it was a winning move
		if (hasWon('X'))
		{
			cout << "Congratulations PlayerX, you have won!!\n\n";
			gameOver = true;
		}
		// check to see if move resulted in a stalemate
		else if (isFull())
		{
			cout << "A Stalemate, too bad!\n\n";
			gameOver = true;
		}
		else
		{
			// Player O makes a move
			move = po.evalAllMoves(*this);
			makeMove('O',move);
			printBoard();
			Sleep(500);
			// check to see if it was the winning move
			if (hasWon('O'))
			{
				cout << "Congratulations PlayerO, you have won!!\n\n";
				gameOver = true;
			}
			// check to see if move resulted in a statemate
			else if (isFull())
			{
				cout << "A Stalemate, too bad!\n\n";
				gameOver = true;
			}
		}		
	// continue until either one player wins or the board fills up
	}while (!gameOver);

	// Round 2: O plays first
	// reset game board 
	reset();
	gameOver = false;
	// announce second round and pause for player to acknowledge
	cout << "Here's round 2: PlayerO goes first!\n";
	system("PAUSE");
	printBoard();
	Sleep(500);
	do
	{
		// Player O makes a move.
		move = po.evalAllMoves(*this);
		makeMove('O',move);
		printBoard();
		Sleep(500);
		// check to see if it is the winning move
		if (hasWon('O'))
		{
			cout << "Congratulations PlayerO, you have won!!\n\n";
			gameOver = true;
		}
		// check for stalemate
		else if (isFull())
		{
			cout << "A Stalemate, too bad!\n\n";
			gameOver = true;
		}
		else
		{
			// Player X makes a move.
			move = px.evalAllMoves(*this);
			makeMove('X',move);
			printBoard();
			Sleep(500);
			// check for a win
			if (hasWon('X'))
			{
				cout << "Congratulations PlayerX, you have won!!\n\n";
				gameOver = true;
			}
			// check for statemate
			else if (isFull())
			{
				cout << "A Stalemate, too bad!\n\n";
				gameOver = true;
			}
		}
			
	}while (!gameOver);
}

/*****************************************************************************
 *  main 
 ****************************************************************************/

int main ()
{
	// in case anyone's using random numbers
	srand((unsigned)time(0));
	// create game board
	Board b;
	// start tournament
	b.hostTournament();
	system("PAUSE");
}