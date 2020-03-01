#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

struct Move
{
	int row,col;
};
char board[3][3]={'_','_','_','_','_','_','_','_','_'}; 	//initially the board is empty
char player ='x',opponent='o';					//us or player by 'x' computer or opponent by 'o'


void Draw()	//to draw the tic tac toe at every moment
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			cout << board[i][j]<<" ";
		}
		cout <<"\n";
	}
}


bool ismovesleft(char board[3][3])
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(board[i][j]=='_')
				return true;
		}
	}
	return false;
}
char Win() // to check if a player has one(to identify which player won)
{			// this can also be replaced by the below function
	if(board[0][0] == 'x' && board[0][1] == 'x' && board[0][2] == 'x')
		return 'x';
	if(board[1][0] == 'x' && board[1][1] == 'x' && board[1][2] == 'x')
		return 'x';
	if(board[2][0] == 'x' && board[2][1] == 'x' && board[2][2] == 'x')
		return 'x';

	if(board[0][0] == 'x' && board[1][0] == 'x' && board[2][0] == 'x')
		return 'x';
	if(board[0][1] == 'x' && board[1][1] == 'x' && board[2][1] == 'x')
		return 'x';
	if(board[0][2] == 'x' && board[1][2] == 'x' && board[2][2] == 'x')
		return 'x';

	if(board[0][0] == 'x' && board[1][1] == 'x' && board[2][2] == 'x')
		return 'x';

	if(board[0][0] == 'o' && board[0][1] == 'o' && board[0][2] == 'o')
		return 'o';
	if(board[1][0] == 'o' && board[1][1] == 'o' && board[1][2] == 'o')
		return 'o';
	if(board[2][0] == 'o' && board[2][1] == 'o' && board[2][2] == 'o')
		return 'o';
	if(board[0][0] == 'o' && board[1][0] == 'o' && board[2][0] == 'o')
		return 'o';
	if(board[0][1] == 'o' && board[1][1] == 'o' && board[2][1] == 'o')
		return 'o';
	if(board[0][2] == 'o' && board[1][2] == 'o' && board[2][2] == 'o')
		return 'o';

	if(board[0][0] == 'o' && board[1][1] == 'o' && board[2][2] == 'o')
		return 'o';

	return '/';
}

int evaluate(char b[3][3]) //this is the evaluate function to check if the game continues or not
{
	int row,col;
	for(row=0;row<3;row++)		//checking for victory via row
	{
		if(b[row][0]==b[row][1] && b[row][1]==b[row][2])
		{
			if(b[row][0]==player)
				return 10;
			else if(b[row][0]==opponent)
				return -10;
		}
	}
	for(col=0;col<3;col++)		//checking for victory via column
	{
		if(b[0][col]==b[1][col] && b[1][col]==b[2][col])
		{
			if(b[0][col]==player)
				return 10;
			else if(b[0][col]=opponent)
				return -10;
		}
	}
	if(b[0][0]==b[1][1] && b[1][1]==b[2][2])		//checking for diagonal victory
	{
		if(b[0][0]==player)
			return 10;
		else if(b[0][0]==opponent)
			return -10;
	}
	if(b[0][2]==b[1][1] && b[2][0]==b[1][1])
	{
		if(b[0][2]==player)
			return 10;
		else if(b[0][2]==opponent)
			return -10;
	}
	return 0;		//if the game has to continue(no one wins yet)

}

int minimax(char board[3][3],int depth,bool ismax)	
{								//this is the minimax function to consider all the possible ways game can proceed
	int score=evaluate(board);
	if(score==10) 	//if maximiser won the game return evaluated score
		return score;
	if(score==-10)		//if minimiser won the game return evaluated score
		return score;
	if(ismovesleft(board)==false)	//no more moves left then it is a tie
		return 0;
	if(ismax)	//if maximisers move
	{
		int best=-1000;
		for(int i=0;i<3;i++)	//check all position if any empty
		{
			for(int j=0;j<3;j++)
			{
				if(board[i][j]='_')
				{
					board[i][j]=player;	//make the move and call recursively to choose max value
					best=max(best,minimax(board,depth+1,!ismax));
					board[i][j]='_';	
				}
			}
		}
		return best;
	}
	else		//if minimisers move
	{
		int best=100;
		for(int i=0;i<3;i++)		//check all position if any empty
		{
			for(int j=0;j<3;j++)
			{
				if(board[i][j]=='_')
				{
					board[i][j]=opponent;		//make the move and call recursively to choose min value
					best=min(best,minimax(board,depth+1,!ismax));
					board[i][j]='_';
				}
			}
		}
		return best;		//returns the value of the board
	}
}

Move findbestmove(char board[3][3])		//returns best possible move present
{
	int bestval=-1000;
	Move bestmove;
	bestmove.row=-1;
	bestmove.col=-1;

	for(int i=0;i<3;i++)	//transverse all position and apply min max at every position
	{						//return the position with best move
		for(int j=0;j<3;j++)
		{
			if(board[i][j]=='_')
			{
				board[i][j]==player;
				int moveval=minimax(board,0,false);
				board[i][j]='_';
				if(moveval>bestval)
				{
					bestmove.row=i;
					bestmove.col=j;
					bestval=moveval;
				}
			}
		}
	}
	printf("the value of the best move is: %d\n",bestval);
	return bestmove;

}

int main()
{

	while(ismovesleft(board))
	{
		int row,col;
		cout<<"YOUR TURN ENTER ROWS AND COLUMN\n";	//asking the player to make his move
		cin>>row>>col;
		board[row+1][col+1]=player;
		Draw();
		if(Win()=='x')				//if(evaluate(board)==10) then player wins
		{
			cout<<"player WINS\n";
			break;
		}
		else if(Win()=='o')			//if(evaluate(board)==-10)  then opponent wins
		{
			cout<<"opponent WINS\n";
			break;
		}
		Move bestmove=findbestmove(board);	//opponent or computer makes the move based on minimax algorithm
		board[bestmove.row][bestmove.col]=opponent;
		Draw();
		if(Win()=='x')
		{
			cout<<"player WINS\n";
			break;
		}
		else if(Win()=='o')
		{
			cout<<"opponent WINS\n";
			break;
		}
	}
}
				
