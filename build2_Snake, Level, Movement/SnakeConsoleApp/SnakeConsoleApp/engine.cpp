#include "engine.h"
#include "colors.h"
#include "objSnake.h"
#include <conio.h>
#include <stdio.h>

//draw functions
void DrawLevel()
{
	const size_t size(256);
	FILE *pFile(NULL);
	CHAR buff[size];
	switch (nLevel) {
		case 1: fopen_s(&pFile, ".\\levels\\level_1", "r"); break;
		default: break;
	}
	if (!pFile) {
		MessageBox(NULL, TEXT("Can not open level file"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	SetColor(cGREY);
	while (!feof(pFile)) {
		fgets(buff, size, pFile);
		Print(buff);
	}
	fclose(pFile);
	return;
}

void DrawSnake(SHORT x, SHORT y)
{
	GoToXY(x, y);
	SetColor(cCYAN);
	putchar('O');
	return;
}

void DrawScore()
{
	//todo
	return;
}

void DrawPanel()
{
	//todo
	return;
}

//game functions
void GameInit()
{
	DrawLevel();
	
	//init obj snake//
	snake.x = 40;
	snake.y = 20;
	snake.direction = ' ';
	snake.speed = MAX_SPEED;

	spd_count = 0;

	(score != 0) ? score = 0 : NULL;

	DrawSnake(snake.x, snake.y);
	return;
}

void GameUpdate()
{
	SHORT x, y;

	spd_count++;
	if (spd_count >= snake.speed) {
		//save the initial coordinates
		x = snake.x;
		y = snake.y;

		//erase the previous position of the snake
		GoToXY(snake.x, snake.y);
		putchar(' ');

		if (snake.direction == 'w') {
			y--;
			if (CheckPosition(x, y) == ' ')
				snake.y--;
			else if (CheckPosition(x, y) == '#')
				snake.direction = STOP;
		} else
		if (snake.direction == 's') {
			y++;
			if (CheckPosition(x, y) == ' ')
				snake.y++;
			else if (CheckPosition(x, y) == '#')
				snake.direction = STOP;
		} else
		if (snake.direction == 'a') {
			x--;
			if (CheckPosition(x, y) == ' ')
				snake.x--;
			else if (CheckPosition(x, y) == '#')
				snake.direction = STOP;
		} else
		if (snake.direction == 'd') {
			x++;
			if (CheckPosition(x, y) == ' ')
				snake.x++;
			else if (CheckPosition(x, y) == '#')
				snake.direction = STOP;
		}

		spd_count = 0;
	}
	return;
}

void GameController(CHAR& bKey, BOOL& gameOver, BOOL& closeConsole)
{
	EventKey(bKey, gameOver, closeConsole);
	EventDraw();
	EventStep(bKey, gameOver, closeConsole);
	return;
}

//controller functions
void EventKey(CHAR& bKey, BOOL& gameOver, BOOL& closeConsole)
{
	bKey = keyboardCheck();
	if (bKey == VK_ESCAPE) {
		gameOver = FALSE;
		closeConsole = TRUE;
	}
	else if (bKey == 'p')
		;//todo
	else if (bKey == 'w' || bKey == 's' || bKey == 'a' || bKey == 'd')
		snake.direction = bKey;

	return;
}

void EventDraw()
{
	DrawSnake(snake.x, snake.y);
	DrawScore();
	DrawPanel();
	return;
}

void EventStep(CHAR& bKey, BOOL& gameOver, BOOL& closeConsole)
{
	if (snake.direction == STOP) {
		gameOver = FALSE;
		//todo Game Over

	}

	Sleep(MAX_STEP);
	return;
}

//additional functions
void GoToXY(const SHORT x, const SHORT y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//-11
	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	COORD cPos;
	cPos.X = x;
	cPos.Y = y;

	if (!SetConsoleCursorPosition(hOut, cPos)) {
		MessageBox(NULL, TEXT("SetConsoleCursorPosition"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	return;
}

void SetColor(const WORD color)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//-11
	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	if (!SetConsoleTextAttribute(hOut, color)) {
		MessageBox(NULL, TEXT("SetConsoleTextAttribute"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	return;
}

void Print(const LPSTR str)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//-11
	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	DWORD cWritten;
	if (!WriteFile(
		hOut, //output handle
		str,  //string
		lstrlenA(str), //string length
		&cWritten, //bytes written
		NULL)) //not overlapped
	{
		MessageBox(NULL, TEXT("WriteFile"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	return;
}



CHAR keyboardCheck()
{
	if (!_kbhit())
		return ' ';
	else
		return _getch();
}

CHAR keyboardCheckPressed()
{
	HANDLE hIn;
	hIn = GetStdHandle(STD_INPUT_HANDLE);//-10
	if (hIn == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	//clear the buffer input
	if (!FlushConsoleInputBuffer(hIn)) {
		MessageBox(NULL, TEXT("FlushConsoleInputBuffer"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

label:
	Sleep(100);
	if (!_kbhit())
		goto label;

	return _getch();
}

void playSound(const DWORD pszSound)
{
	if (!PlaySound(
		MAKEINTRESOURCE(pszSound),
		GetModuleHandle(NULL),
		SND_RESOURCE | SND_ASYNC))
	{
		MessageBox(NULL, TEXT("PlaySound"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	return;
}

void inKey(const DWORD color)
{
	GoToXY(25, 40);
	SetColor(color);
	Print("Press any key to continue...");
	_getch();

	return;
}

CHAR CheckPosition(const SHORT x, const SHORT y)
{
	const size_t length(1);
	CHAR buff[length];
	DWORD cRead;

	GoToXY(x, y);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//-11
	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD cPos = { 0, 0 };
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}
	cPos = csbi.dwCursorPosition;

	if (!ReadConsoleOutputCharacter(hOut, (LPTSTR)buff, (DWORD)length, cPos, (LPDWORD)&cRead)) {
		MessageBox(NULL, TEXT("ReadConsoleOutputCharacter"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	return *buff;
}
