#include <SFML/Graphics.hpp>
#include<iostream>
#include <windows.h>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
int turn = 0, BoardRows = 8, BoardColumns = 8, row, column, Player1Winning = 0, Player2Winning = 0, MouseMovment = 0;
char grid[8][8], win = 'X';
bool connect4 = 0, MainMenu = 1, Win = 1;
RenderWindow window(sf::VideoMode(1280, 720), "Game Bundle", Style::Close);
Font font;
struct Moves
{
	int x, y;
}undo[64];
void TextProperties(Text& text, string title, int x, int y, int size)
{
	text.setFont(font);
	text.setString(title);
	text.setCharacterSize(size);
	text.setFillColor(Color::White);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(5);
	text.setPosition(x, y);

}
void Buttons(Sprite UndoButton, Sprite MainMenuButton, Sprite NewGameButton)
{
	Vector2i mousePos = sf::Mouse::getPosition(window);
	Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	UndoButton.setPosition(900, 370);
	NewGameButton.setPosition(900, 450);
	MainMenuButton.setPosition(900, 540);
	window.draw(UndoButton);
	window.draw(NewGameButton);
	window.draw(MainMenuButton);
	if (NewGameButton.getGlobalBounds().contains(mousePosF) && Mouse::isButtonPressed(Mouse::Left))
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				grid[i][j] = 'X';
		turn = 0;
		Win = 1;
		win = 'X';
	}
	if (UndoButton.getGlobalBounds().contains(mousePosF) && Mouse::isButtonPressed(Mouse::Left) && turn > 0)
	{
		turn--;
		grid[undo[turn].x][undo[turn].y] = 'X';
		if (Win == 0)
		{
			Win = 1;

			if (win == '#')
				Player1Winning--;
			else if (win == '*')
				Player2Winning--;
			win = 'X';
		}
		//Sleep(85);
	}
	if (MainMenuButton.getGlobalBounds().contains(mousePosF) && Mouse::isButtonPressed(Mouse::Left))
	{
		MainMenu = 1;
		connect4 = 0;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				grid[i][j] = 'X';
		turn = 0;
		Win = 1;
		win = 'X';
		//Sleep(150);

	}
}
void playerPos(char player, int ColumnDrop)
{
	for (int i = BoardRows - 1; i >= 0; i--)
	{
		if (grid[i][ColumnDrop - 1] == 'X')
		{
			grid[i][ColumnDrop - 1] = player;
			row = i, column = ColumnDrop - 1;
			undo[turn].x = i, undo[turn].y = ColumnDrop - 1;
			break;
		}
	}
}
void display(Sprite rc, Sprite bc, Sprite UndoButton, Sprite MainMenuButton, Sprite NewGameButton, Text& Player1, Text& Player2)
{
	system("CLS");
	int w = 800 / BoardColumns, l = 660 / BoardRows;
	for (int i = 0; i < BoardRows; i++)
	{
		for (int j = 0; j < BoardColumns; j++)
		{
			if (grid[i][j] == '#')
			{
				if (i == 0)
					rc.setPosition(65 + j * w, 78 + i * l);
				else if (i < 3)
					rc.setPosition(65 + j * w, 68 + i * l);
				else
					rc.setPosition(65 + j * w, 55 + i * l);
				window.draw(rc);
			}
			else if (grid[i][j] == '*')
			{
				if (i == 0)
					bc.setPosition(65 + j * w, 78 + i * l);
				else if (i < 3)
					bc.setPosition(65 + j * w, 68 + i * l);
				else
					bc.setPosition(65 + j * w, 55 + i * l);
				window.draw(bc);
			}
			cout << grid[i][j] << "\t";
		}
		cout << endl;
	}
	Buttons(UndoButton, MainMenuButton, NewGameButton);

	if (!((Mouse::getPosition(window).x) <= 860 && (Mouse::getPosition(window).x) >= 60 && (Mouse::getPosition(window).y) >= 0 && (Mouse::getPosition(window).y) <= 700))
	{
		if (turn % 2 == 0)
		{
			rc.setPosition(MouseMovment, 0);
			window.draw(rc);
		}
		else
		{
			bc.setPosition(MouseMovment, 0);
			window.draw(bc);
		}

	}
	if ((Mouse::getPosition(window).x) <= 860 && (Mouse::getPosition(window).x) >= 60 && (Mouse::getPosition(window).y) >= 0 && (Mouse::getPosition(window).y) <= 700)
	{
		if (turn % 2 == 0)
		{
			rc.setPosition(Mouse::getPosition(window).x, 0);
			window.draw(rc);
			MouseMovment = Mouse::getPosition(window).x;
		}
		else
		{
			bc.setPosition(Mouse::getPosition(window).x, 0);
			window.draw(bc);
			MouseMovment = Mouse::getPosition(window).x;
		}
	}
	string Player1Score = to_string(Player1Winning);
	string Player2Score = to_string(Player2Winning);
	TextProperties(Player1, Player1Score, 980, 620, 50);
	TextProperties(Player2, Player2Score, 1200, 620, 50);

	rc.setPosition(870, 620);
	bc.setPosition(1070, 620);
	window.draw(rc);
	window.draw(bc);
	window.draw(Player1);
	window.draw(Player2);

}
void winnerDisplayVER(int i, int j, Sprite winnerx)
{
	int w = 800 / BoardColumns, l = 660 / BoardRows, count = 0;
	for (; count < 4; i++)
	{
		winnerx.setPosition(90 + j * w, 70 + i * l);
		window.draw(winnerx);
		count++;
	}
	window.display();
}
void winnerDisplayHOR(int i, int j, Sprite winnerx)
{
	int w = 800 / BoardColumns, l = 660 / BoardRows, count = 0;
	for (; count < 4; j--)
	{
		winnerx.setPosition(90 + j * w, 70 + i * l);
		window.draw(winnerx);
		count++;
	}
	window.display();
}
void winnerDisplayDigRight(int i, int j, Sprite winnerx)
{
	int w = 800 / BoardColumns, l = 660 / BoardRows, count = 0;
	for (; count < 4; i++, j--)
	{
		winnerx.setPosition(90 + j * w, 70 + i * l);
		window.draw(winnerx);
		count++;
	}
	window.display();

}
void winnerDisplayDigLeft(int i, int j, Sprite winnerx)
{
	int w = 800 / BoardColumns, l = 660 / BoardRows, count = 0;
	for (; count < 4; i++, j++)
	{
		winnerx.setPosition(90 + j * w, 70 + i * l);
		window.draw(winnerx);
		count++;
	}
	window.display();

}
bool  winner(Sprite winnerx)
{
	if (turn >= 6)
	{
		bool wi = false;
		for (int i = 8 - 1; i >= 0; i--)
		{
			int cnt = 0;
			for (int j = 1; j < 8; j++)
			{
				if (grid[i][j] == grid[i][j - 1] && grid[i][j] != 'X')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = grid[i][j];
					winnerDisplayHOR(i, j, winnerx);
					wi = true;
				}
			}
		}
		for (int j = 0; j < 8; j++)
		{
			int cnt = 0;
			for (int i = 8 - 2; i >= 0; i--)
			{
				if (grid[i][j] == grid[i + 1][j] && grid[i][j] != 'X')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = grid[i][j];
					winnerDisplayVER(i, j, winnerx);
					wi = true;
				}
			}
		}
		for (int row = 2; row < 8 - 1; row++)
		{
			for (int i = row, j = 1, cnt = 0; j < 8 && i >= 0; i--, j++)
			{
				if (grid[i][j] == grid[i + 1][j - 1] && grid[i][j] != 'X')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = grid[i][j];
					winnerDisplayDigRight(i, j, winnerx);
					wi = true;
				}
			}
		}
		for (int col = 2; 8 - col >= 3; col++)
		{
			for (int i = 8 - 2, j = col, cnt = 0; i >= 0 && j < 8; i--, j++)
			{
				if (grid[i][j] == grid[i + 1][j - 1] && grid[i][j] != 'X')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = grid[i][j];
					winnerDisplayDigRight(i, j, winnerx);
					wi = true;
				}
			}
		}
		for (int row = 2; row < 8 - 1; row++)
		{
			for (int i = row, j = 8 - 2, cnt = 0; j >= 0 && i >= 0; i--, j--)
			{
				if (grid[i][j] == grid[i + 1][j + 1] && grid[i][j] != 'X')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = grid[i][j];
					winnerDisplayDigLeft(i, j, winnerx);
					wi = true;
				}
			}
		}
		for (int col = 8 - 3; col > 1; col--)
		{
			for (int i = 8 - 2, j = col, cnt = 0; i >= 0 && j >= 0; i--, j--)
			{
				if (grid[i][j] == grid[i + 1][j + 1] && grid[i][j] != 'X')
					cnt++;
				else
					cnt = 0;
				if (cnt == 3)
				{
					win = grid[i][j];
					winnerDisplayDigLeft(i, j, winnerx);
					wi = true;
				}
			}
		}
		if (wi)
			return true;
	}
	return false;
}
void resize(Sprite& sprite, Vector2f targetSize)
{
	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);
}
void WinningPrint(Sprite Congrants, Sprite PlayAgainButton, Sprite ExitButton)
{
	Vector2i mousePos = sf::Mouse::getPosition(window);
	Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	Congrants.setPosition(100, 200);
	PlayAgainButton.setPosition(150, 400);
	ExitButton.setPosition(500, 420);
	window.draw(ExitButton);
	window.draw(PlayAgainButton);
	window.draw(Congrants);
	if (turn % 2 == 0 && Win)
	{
		Win = 0;
		Player2Winning++;
	}
	else if (turn % 2 != 0 && Win)
	{
		Win = 0;
		Player1Winning++;
	}
	if (PlayAgainButton.getGlobalBounds().contains(mousePosF) && Mouse::isButtonPressed(Mouse::Left))
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				grid[i][j] = 'X';
		turn = 0;
		Win = 1;
		win = 'X';
	}
	if (ExitButton.getGlobalBounds().contains(mousePosF) && Mouse::isButtonPressed(Mouse::Left))
		window.close();
	window.display();
}
int main()
{
	ios_base::sync_with_stdio(false);
	Text Player1, Player2;
	SoundBuffer buffer;
	buffer.loadFromFile("Audio/drop.wav");
	Sound sound;
	sound.setBuffer(buffer);
	Texture Backgroundpic, boardpic, blackcircle, redcircle, WinnerHighlight, UndoB, NewGameB, MainMenuB, PlayAgainB, ExitB, CongrantsImage, ColumnError, menu;
	font.loadFromFile("TimesNewRoman.ttf");
	ColumnError.loadFromFile("images/ThisColumnisFull.png");
	Backgroundpic.loadFromFile("images/Backgroundpic.png");
	blackcircle.loadFromFile("images/blackcircle.png");
	redcircle.loadFromFile("images/redcircle.png");
	boardpic.loadFromFile("images/board.png");
	WinnerHighlight.loadFromFile("images/x.png");
	//MainMenuB.loadFromFile("images/MainMenu.png");
	UndoB.loadFromFile("images/Undo.png");
	menu.loadFromFile("images/main.png");
	NewGameB.loadFromFile("images/NewGame.png");
	PlayAgainB.loadFromFile("images/PlayAgain.png");
	ExitB.loadFromFile("images/Exit.png");
	CongrantsImage.loadFromFile("images/congrats.png");
	Texture Box1, Box2, Box3, Box4, Box5, Box6, Box7, Box8, Box9, X, O, background, noWin;
	noWin.loadFromFile("images/nowinner.png");
	ColumnError.setSmooth(true);
	boardpic.setSmooth(true);
	Backgroundpic.setSmooth(true);
	blackcircle.setSmooth(true);
	redcircle.setSmooth(true);
	WinnerHighlight.setSmooth(true);
	UndoB.setSmooth(true);
	NewGameB.setSmooth(true);
	MainMenuB.setSmooth(true);
	PlayAgainB.setSmooth(true);
	ExitB.setSmooth(true);
	CongrantsImage.setSmooth(true);
	Sprite bg(Backgroundpic), board(boardpic), rc(redcircle), bc(blackcircle), winnerX(WinnerHighlight), UndoButton(UndoB), MainMenuButton(MainMenuB), NewGameButton(NewGameB), PlayAgainButton(PlayAgainB), ExitButton(ExitB), Congrants(CongrantsImage), ColumnFull(ColumnError), b1(Box1), b2(Box2), b3(Box3), b4(Box4), b5(Box5), b6(Box6), b7(Box7), b8(Box8), b9(Box9), x(X), o(O), bg2(background), noWinner(noWin), main(menu);
	board.setPosition(60, 60);
	Vector2f BoardSize(800, 650), BackgroundSize(1280, 720), CircleSize(90, 72.5), Winner_X_Size(40, 40), UndoSize(200, 80), NewGameSize(300, 80), MainMenuSize(300, 80), CongrantsSize(600, 250), PlayAgainSize(180, 120), ExitSize(100, 90), nowinnerSize(300, 200), menusize(1280, 720);
	resize(rc, CircleSize);
	resize(bc, CircleSize);
	resize(bg, BackgroundSize);
	resize(board, BoardSize);
	resize(winnerX, Winner_X_Size);
	resize(UndoButton, UndoSize);
	resize(NewGameButton, NewGameSize);
	resize(MainMenuButton, MainMenuSize);
	resize(Congrants, CongrantsSize);
	resize(PlayAgainButton, PlayAgainSize);
	resize(ExitButton, ExitSize);
	resize(noWinner, nowinnerSize);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			grid[i][j] = 'X';
	while (window.isOpen())
	{
		window.setFramerateLimit(60);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		Vector2i mousePos = sf::Mouse::getPosition(window);
		Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
		

		window.clear();
		window.draw(bg);
		display(rc, bc, UndoButton, MainMenuButton, NewGameButton, Player1, Player2);
		window.draw(board);
		if (turn == 64)
		{
			noWinner.setPosition(400, 200);
			window.draw(noWinner);
		}
		if (winner(winnerX))
		{
			winner(winnerX);
			WinningPrint(Congrants, PlayAgainButton, ExitButton);
			continue;
		}
		window.display();
		if (Mouse::isButtonPressed(Mouse::Left) && (Mouse::getPosition(window).x) <= 860 && (Mouse::getPosition(window).x) >= 60 && (Mouse::getPosition(window).y) >= 0 && (Mouse::getPosition(window).y) <= 700)
		{
			int ColumnDrop;
			ColumnDrop = ceil(((double)(Mouse::getPosition(window).x) - 60) / (800 / BoardColumns));
			playerPos('X', ColumnDrop);
			if (grid[0][ColumnDrop - 1] != 'X')
			{
				ColumnFull.setPosition(50, 250);
				window.draw(ColumnFull);
				window.display();
				Sleep(150);
				continue;
			}
			int y = 0;
			while (y <= (60 + row * (660 / 8)))
			{
				window.clear();
				window.draw(bg);
				display(rc, bc, UndoButton, MainMenuButton, NewGameButton, Player1, Player2);
				if (turn % 2 == 0)
				{
					rc.setPosition(65 + (ColumnDrop - 1) * 100, y);
					window.draw(rc);
				}
				else
				{
					bc.setPosition(65 + (ColumnDrop - 1) * 100, y);
					window.draw(bc);
				}
				y += 110;
				window.draw(board);
				window.display();
			}
			if (turn % 2 == 0)
				playerPos('#', ColumnDrop);
			else
				playerPos('*', ColumnDrop);
			sound.play();
			turn++;
		}
		
	}
}
