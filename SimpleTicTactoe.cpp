// this is a simple tic tac toe without any minimax algorithm
//two players palys


#include <iostream>
using namespace std;
char matrix[3][3] = {'1','2','3','4','5','6','7','8','9'};
char player ='X';
void Draw()	// for drawing the tic tac toe table which is in form of 2d matrix
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			cout << matrix[i][j]<<" ";
		}
		cout <<"\n";
	}
}
void Input()
{
	int a;
	cout<<"PRESS NUMBER YOU WANT TO CHOOSE";
	cin>>a;

	if(a==1)					//making x or 0 based upon the place choosen and players turn
		matrix[0][0]=player;
	else if(a==2)
		matrix[0][1]=player;
	else if(a==3)
		matrix[0][2]=player;
	else if(a==4)
		matrix[1][0]=player;
	else if(a==5)
		matrix[1][1]=player;
	else if(a==6)
		matrix[1][2]=player;
	else if(a==7)
		matrix[2][0]=player;
	else if(a==8)
		matrix[2][1]=player;
	else if(a==9)
		matrix[2][2]=player;
}
void Player()		//reverses the player after every turn
{
	if(player=='X')
		player='0';
	else
		player='X';
}
char Win()			//check if the player has won to end the game
{
	if(matrix[0][0] == 'X' && matrix[0][1] == 'X' && matrix[0][2] == 'X')
		return 'X';
	if(matrix[1][0] == 'X' && matrix[1][1] == 'X' && matrix[1][2] == 'X')
		return 'X';
	if(matrix[2][0] == 'X' && matrix[2][1] == 'X' && matrix[2][2] == 'X')
		return 'X';

	if(matrix[0][0] == 'X' && matrix[1][0] == 'X' && matrix[2][0] == 'X')
		return 'X';
	if(matrix[0][1] == 'X' && matrix[1][1] == 'X' && matrix[2][1] == 'X')
		return 'X';
	if(matrix[0][2] == 'X' && matrix[1][2] == 'X' && matrix[2][2] == 'X')
		return 'X';

	if(matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X')
		return 'X';

	if(matrix[0][0] == '0' && matrix[0][1] == '0' && matrix[0][2] == '0')
		return '0';
	if(matrix[1][0] == '0' && matrix[1][1] == '0' && matrix[1][2] == '0')
		return '0';
	if(matrix[2][0] == '0' && matrix[2][1] == '0' && matrix[2][2] == '0')
		return '0';
	if(matrix[0][0] == '0' && matrix[1][0] == '0' && matrix[2][0] == '0')
		return '0';
	if(matrix[0][1] == '0' && matrix[1][1] == '0' && matrix[2][1] == '0')
		return '0';
	if(matrix[0][2] == '0' && matrix[1][2] == '0' && matrix[2][2] == '0')
		return '0';

	if(matrix[0][0] == '0' && matrix[1][1] == '0' && matrix[2][2] == '0')
		return '0';

	return '/';
}
int main()
{
	Draw();
	while(1)		
	{
		Input();
		Draw();
		if(Win()=='X')
		{
			cout<<"X WINS\n";
			break;
		}
		else if(Win()=='0')
		{
			cout<<"Y WINS\n";
			break;
		}
		Player();
	}


}
