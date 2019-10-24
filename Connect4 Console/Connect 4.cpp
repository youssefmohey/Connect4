#include <iostream>
#include<string>
#include <Windows.h>

using namespace std;
struct data
{
	string player;
	int score;
}players[2];
void inputs(int& rows, int& columns)
{
	system("cls");
	cout << "Enter number of rows : ";
	cin >> rows;
	while (rows < 4 || cin.fail() || rows>10)
	{
		cin.clear();
		cin.ignore();
		cin.sync();   //clear the input buffer
		cout << "Number of rows should be an integer number greater than or equal to 4 and less than or equal 10: ";
		cin >> rows;
	}
	cout << "Enter number of columns : ";
	cin >> columns;
	while (columns < 4 || cin.fail() || columns>10)
	{
		cin.clear();
		cin.ignore();
		cin.sync();   //clear the input buffer
		cout << "Number of rows should be an integer number greater than or equal to 4 and less than or equal 10 : ";
		cin >> columns;
	}
}
void display(char** board, int rows, int columns)
{
	system("cls");
	cout << endl << "\t\t\t" << players[0].player << " score : " << players[0].score << "\t\t\t\t" << players[1].player << " score : " << players[1].score << endl;
	for (int l1 = 0; l1 < rows; l1++) 
	{
		cout << "\t\t\t";
		for (int l2 = 0; l2 < columns; l2++) 
			cout << " ___\t"; // celling
		cout << endl; cout << "\t\t\t";
		for (int l3 = 0; l3 < columns; l3++) 
		{
			cout << "| ";
			if (board[l1][l3] == 'X')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); cout << board[l1][l3];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (board[l1][l3] == 'O')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); 
				cout << board[l1][l3];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else  
				cout << board[l1][l3]; 
			cout << " |\t";
		}
		cout << endl;
	}
	cout << "\t\t\t";
	for (int l4 = 1; l4 <= columns; l4++) 
		cout << "--" << l4 << "--\t";
	cout << endl;
}
void Pos(char** board, int rows, int columns, int& turn)
{
	display(board, rows, columns);
	int column = 0;
	double col = 0;
	do
	{

		cin.sync();
		if (turn % 2 == 0)
			cout << players[0].player << " : ";
		else
			cout << players[1].player << " : ";
		cin >> col;
		col--;
		column = col;
		if (column<0 || column>columns - 1)
			cout << "Enter number between 1 and " << columns << endl;
		else if (board[0][column] != '#')
			cout << "This column is completely full try another column" << endl;
		else if (col - column != 0)
			cout << "Enter integer number between 1 and " << columns << endl;
	} while (column<0 || column>columns - 1 || col - column != 0 || board[0][column] != '#');
	for (int i = rows - 1; i >= 0; i--)
	{	
		if (board[i][column] == '#')
		{
			if (turn % 2 == 0)
			{
				board[i][column] = 'X';

			}
				
			else
				board[i][column] = 'O';
			break;
		}
	}
	turn++;
}
bool  winner(char** board, int rows, int columns, char& win, int turn)
{
	if (turn >= 6)
	{
		for (int i = rows - 1; i >= 0; i--)
		{
			int cnt = 0;
			for (int j = 1; j < columns; j++)
			{
				if (board[i][j] == board[i][j - 1] && board[i][j] != '#')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = board[i][j];
					cout << "1";
					Sleep(10);
					return true;
				}
			}
		}
		for (int j = 0; j < columns; j++)
		{
			int cnt = 0;
			for (int i = rows - 2; i >= 0; i--)
			{
				if (board[i][j] == board[i + 1][j] && board[i][j] != '#')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = board[i][j];
					cout << 2;
					Sleep(10);
					return true;
				}
			}
		}
		for (int row = 2; row < rows - 1; row++)
		{
			for (int i = row , j = 1, cnt = 0; j < columns && i >= 0; i--, j++)
			{
				if (board[i][j] == board[i + 1][j - 1] && board[i][j] != '#')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = board[i][j];
					cout << 3;
					Sleep(10);
					return true;
				}
			}
		}
		for (int col = 2; columns - col >= 3; col++)
		{
			for (int i = rows - 2, j = col, cnt = 0; i >= 0 && j < columns; i--, j++)
			{
				if (board[i][j] == board[i + 1][j - 1] && board[i][j] != '#')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = board[i][j];
					return true;
				}
			}
		}
		for (int row = 2; row < rows - 1; row++)
		{
			for (int i = row, j = columns - 2, cnt = 0; j >= 0 && i >= 0; i--, j--)
			{
				if (board[i][j] == board[i + 1][j + 1] && board[i][j] != '#')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = board[i][j];
					cout << 3;
					Sleep(10);
					return true;
				}
			}
		}
		for (int col = columns-3; col > 1; col--)
		{
			for (int i = rows - 2, j = col, cnt = 0; i >= 0 && j >=0; i--, j--)
			{
				if (board[i][j] == board[i + 1][j + 1] && board[i][j] != '#')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = board[i][j];
					return true;
				}
			}
		}
	}
	return false;
}
int main()
{
	int again;
	cout << "Enter Player1 Name : ";
	getline(cin, players[0].player);
	cin.sync();
	cout << "Enter Player2 Name : ";
	getline(cin, players[1].player);
	while (players[0].player == players[1].player)
	{
		cin.sync();
		cout << "Player2 Name should not be the same as player1 name : ";
		getline(cin, players[1].player);
	}
	do
	{
		int rows, columns, turn = 0;
		//string player1, player2;
		char win = '#';
		inputs(rows, columns);
		char** board = new  char* [rows];
		for (int i = 0; i < rows; i++)
			board[i] = new char[columns];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
				board[i][j] = '#';
		}
		while (!winner(board, rows, columns, win, turn) && turn < 64)
		{
			Pos(board, rows, columns, turn);
		}
		display(board, rows, columns);
		if (turn == 64 && !winner(board, rows, columns, win,turn))
			cout << "No one Wons try again" << endl;
		else
		{
			if ((turn - 1) % 2 == 0)
			{
				cout << "Congratualtions " << players[0].player << endl;
				players[0].score++;
			}
			else
			{
				cout << "Congratualtions " << players[1].player << endl;
				players[1].score++;
			}
		}
			
		for (int i = 0; i < rows; i++)
			delete[]board[i];
		delete[] board;
		cout << "if you want to play again press 1 else press zero : ";
		cin >> again;
		while (again != 0 && again != 1)
		{
			cout << "if you want to playe again press 1 else press zero : ";
			cin >> again;
		}
	} while (again);
	system("cls");
	cout << "Good bye see you another time";
}
