class PlayerX
{
private: 
	char playermark, oppmark;
	int keep [7];
	char board[6][7];
public:
	PlayerX ();
	PlayerX(char mark);

	int checkPattern_xx1_xxx_1xx(char board[][7],char mark, int row, int col,int bias);
	int checkPattern_1xx_xxx_xx1(char board[][7],char mark, int row, int col,int bias);
	int checkPattern_x1x_xxx_x1x(char board[][7],char mark, int row, int col,int bias);
	int checkPattern_xxx_1x1_xxx(char board[][7],char mark, int row, int col,int bias);
	
	int getMax(int a, int b);
	int getMin(int a, int b);
	int bestMove(int scores[]);
	int evalAllMoves (Board b);
	int evalMove (int col, Board b);
	int countMarks(char board[][7], char mark, int start_r, int start_c,int step_r, int step_c);



};

PlayerX::PlayerX ()
{
//TODO SWAP X AND O FOR PLAYER O
//playermark='O';oppmark='X';	
	playermark='X';
	oppmark='O';
}

PlayerX::PlayerX(char mark)
{
	playermark=mark;
	if (mark=='X')
		oppmark='O';
	else 
		oppmark='X';
}

int PlayerX:: countMarks(char board[][7], char mark, int start_r, int start_c,int step_r, int step_c)
{
	int count=0;
	if (start_c<0&&start_r<0&&start_c>6&&start_r>5)// checking for out of bounds
		return -1;
	
	//checking for the representing letter 'o' or 'x'
	for (int col=start_c, row=start_r;col>=0&&row>=0&&col<7&&row<6;col+=step_c,row+=step_r)
	{
		if (board[row][col]==mark)
			count++;
		else
			break;
	}
	return count;
}

//check diagonal /
int PlayerX:: checkPattern_xx1_xxx_1xx(char board[][7],char mark, int row, int col,int bias)
{
	int count1=countMarks(board,mark,row+1,col-1,1,-1);
	int count2=countMarks(board, mark, row-1,col+1,-1,1);
	int counttotal=count1+count2;

	if (counttotal>2)
	{
		return 100+bias;
	}

	else if (counttotal>1)
	{
		//count number of blocking marks
		int c1=countMarks(board,'e',row+1+count1,col-1-count1,1,-1);
		int c2=countMarks(board,'e',row-1-count2,col+1+count2,-1,1);

		if (c1>0&&c2>0)			//if no blocks
			return 80+bias;
		else if (c1>0||c2>0)	//if there is one block
			return 65+bias;
		else					//if there is two blocks
			return 10+bias;
	}
	else if (counttotal>0)
	{
		//count number of blocking marks
		int c1=countMarks(board,'e',row+1+count1,col-1-count1,1,-1);
		int c2=countMarks(board,'e',row-1-count2,col+1+count2,-1,1);

		if (c1>0&&c2>0)			//if no blocks
			return 75+bias;
		else if (c1>0||c2>0)	//if there is one block
			return 60+bias;
		else					// if there is two blocks
			return 10+bias;
	}
	else
		return 5;

}

// check diagonal \ 
int PlayerX:: checkPattern_1xx_xxx_xx1(char board[][7],char mark, int row, int col,int bias)
{
	int count1=countMarks(board,mark,row-1,col-1,-1,-1);
	int count2=countMarks(board, mark, row+1,col+1,1,1);
	int counttotal=count1+count2;

	if (counttotal>2)
	{
		return 100+bias;
	}
	else if (counttotal>1)
	{
		//count number of blocking marks
		int c1=countMarks(board,'e',row-1-count1,col-1-count1,-1,-1);
		int c2=countMarks(board,'e',row+1+count2,col+1+count2,1,1);

		if (c1>0&&c2>0)			//if there is no block
			return 80+bias;
		else if (c1>0||c2>0)	//if there is one block
			return 65+bias;
		else					//if there is two blocks
			return 10+bias;
	}
	else if (counttotal>0)
	{
		//count number of blocking marks
		int c1=countMarks(board,'e',row-1-count1,col-1-count1,-1,-1);
		int c2=countMarks(board,'e',row+1+count2,col+1+count2,1,1);

		if (c1>0&&c2>0)			//if no blocks
			return 75+bias;
		else if (c1>0||c2>0)	//if there is one block
			return 60+bias;
		else					// if there is two blocks
			return 10+bias;
	}
	else
		return 5;
}
//check vertical
int PlayerX:: checkPattern_x1x_xxx_x1x(char board[][7],char mark, int row, int col,int bias)
{
	int count1=countMarks(board,mark,row-1,col,-1,0);
	int count2=countMarks(board, mark, row+1,col,1,0);
	int counttotal=count1+count2;

	if (counttotal>2)
	{
		return 100+bias;
	}
	else if (counttotal>1)
	{
		int c1=countMarks(board,'e',row-1-count1,col,-1,0);
		int c2=countMarks(board,'e',row+1+count2,col,1,0);

		if (c1>0&&c2>0)			// if no blocks
			return 80+bias;
		else if (c1>0||c2>0)	//if there is one block
			return 65+bias;
		else					// if there is two blocks
			return 10+bias;
	}
	else if (counttotal>0)
	{
		//count number of blocking marks
		int c1=countMarks(board,'e',row-1-count1,col,-1,0);
		int c2=countMarks(board,'e',row+1+count2,col,1,0);

		if (c1>0&&c2>0)			//if no blocks
			return 75+bias;
		else if (c1>0||c2>0)	//if there is one block
			return 60+bias;
		else					// if there is two blocks
			return 10+bias;
	}
	else
		return 5;
}
//check horizontal
int PlayerX:: checkPattern_xxx_1x1_xxx(char board[][7],char mark, int row, int col,int bias)
{
	int count1=countMarks(board,mark,row,col-1,0,-1);
	int count2=countMarks(board, mark, row,col+1,0,1);
	int counttotal=count1+count2;

	if (counttotal>2)
	{
		return 100+bias;
	}
	else if (counttotal>1)
	{
		//count number of blocking marks
		int c1=countMarks(board,'e',row,col-1-count1,0,-1);
		int c2=countMarks(board,'e',row,col+1+count2,0,1);

		if (c1>0&&c2>0)			//if there is no block
			return 80+bias;	
		else if (c1>0||c2>0)	//if there is one block
			return 65+bias;
		else					//if there is two blocks
			return 10+bias;
	}
	else if (counttotal>0)
	{
		//count number of blocking marks
		int c1=countMarks(board,'e',row,col-1-count1,0,-1);
		int c2=countMarks(board,'e',row,col+1+count2,0,1);

		if (c1>0&&c2>0)			//if no blocks
			return 75+bias;
		else if (c1>0||c2>0)	//if there is one block
			return 60+bias;
		else					// if there is two blocks
			return 10+bias;
		
	}
	else
		return 5;
}

int PlayerX:: getMax(int a, int b)
{
	if (a>b)
		return a;
	else 
		return b;
}
int PlayerX:: getMin(int a, int b)
{
	if (a<b)
		return a;
	else 
		return b;
}

int PlayerX:: evalAllMoves (Board b)
{
	int scores [7];
	for (int col=0; col<7; col++)
	{	
		scores[col]=evalMove(col, b);
		
	}
	return bestMove(scores);//int scores[]	
	
}

int PlayerX:: evalMove (int col, Board b)
{
	
	char board [6][7];
	if (b.checkMove(col)==false)
	{
		return -1;
	}
	b.getArray(board);
	
	int count=0;
	//int countarr[4];
	int row;
	int maxwin=0;
	int maxblock=0;
	int maxlose=0;
	for (row=5; row>=0;row--)
	{	
		if (board[row][col]=='e')
			break;
	}
	
	//check for wins, keep best score
	maxwin=getMax(maxwin,checkPattern_xx1_xxx_1xx(board,playermark,row,col,0));
	maxwin=getMax(maxwin,checkPattern_1xx_xxx_xx1(board,playermark,row,col,0));
	maxwin=getMax(maxwin,checkPattern_xxx_1x1_xxx(board,playermark,row,col,0));
	maxwin=getMax(maxwin,checkPattern_x1x_xxx_x1x(board,playermark,row,col,0));
	
	//check for blocks, keep best score
	maxblock=getMax(maxblock,checkPattern_xx1_xxx_1xx(board,oppmark,row,col,-1));
	maxblock=getMax(maxblock,checkPattern_1xx_xxx_xx1(board,oppmark,row,col,-1));
	maxblock=getMax(maxblock,checkPattern_xxx_1x1_xxx(board,oppmark,row,col,-1));
	maxblock=getMax(maxblock,checkPattern_x1x_xxx_x1x(board,oppmark,row,col,-1));
	
	//check for winning move for opponent one space up, then reduce score
	maxlose=getMax(maxlose,checkPattern_xx1_xxx_1xx(board,oppmark,row-1,col,0));
	maxlose=getMax(maxlose,checkPattern_1xx_xxx_xx1(board,oppmark,row-1,col,0));
	maxlose=getMax(maxlose,checkPattern_xxx_1x1_xxx(board,oppmark,row-1,col,0));
	maxlose=getMax(maxlose,checkPattern_x1x_xxx_x1x(board,oppmark,row-1,col,0));

	if (maxlose==100)// if subsequent move loses 
		return 0;
	else if (maxwin>maxblock) //if move is better than blocking
		return maxwin;
	else if (maxblock>maxwin)	//if blocking move is better
		return maxblock;
	else if (maxblock>maxlose)	//if blocking is better than losing
		return maxblock;
	else						//if subsequent move give the opp the advantage
		return 0;
}
//given a tie, the best move will start with the leftmost column
int PlayerX:: bestMove (int scores[])
{
	int col=0;
	int maxscore=-2;
	for (int i=0;i<7;i++)
	{
		if(maxscore<scores[i])
		{
			maxscore=scores[i];
			col=i;
		}
	}
	return col;

}