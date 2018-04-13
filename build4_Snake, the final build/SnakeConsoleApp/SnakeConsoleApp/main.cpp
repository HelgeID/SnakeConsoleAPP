#include <Windows.h>
#include <tchar.h>

#include "interface.h"
#include "engine.h"
#include "colors.h"

#define MAX_WIDTH 82 //width of the console
#define MAX_HIGHT 42 //height of the console

//flags
CHAR bKey;
BOOL gameOver;
BOOL closeConsole;

HANDLE hOut;

//function of the console
void SetWindowTitle(const LPTSTR);
void SetWindowSize(const SHORT, const SHORT);
void HideCursor();

int main()
{
	//get handle//
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//-11
	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	SetWindowTitle("Snake Demo");
	SetWindowSize(MAX_WIDTH, MAX_HIGHT);
	HideCursor();

	MainMenu(hOut, bKey, gameOver, closeConsole);
	while (closeConsole == FALSE)
	{
		GameInit();
		while (gameOver == TRUE)
		{
			GameController(bKey, gameOver, closeConsole);
			GameUpdate();
		}
		if (gameOver == FALSE)
			GameOverMenu(bKey);
		MainMenu(hOut, bKey, gameOver, closeConsole);
	}

	return EXIT_SUCCESS;
}

void SetWindowTitle(const LPTSTR lpConsoleTitle)
{
	TCHAR* tcConsoleTitle = _T(lpConsoleTitle);
	if (!SetConsoleTitle(tcConsoleTitle)) {
		MessageBox(NULL, TEXT("SetConsoleTitle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}
	return;
}

void SetWindowSize(const SHORT wd, const SHORT ht)
{
	//get handle//
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//-11
	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	//CONSOLE_SCREEN_BUFFER_INFO csbiInfo;//not uses

	//set size of buffer//
	COORD coordBuff = { wd, ht };
	if (!SetConsoleScreenBufferSize(hOut, coordBuff)) {
		MessageBox(NULL, TEXT("SetConsoleScreenBufferSize"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	/* not uses
	if (!GetConsoleScreenBufferInfo(hOut, &csbiInfo)) {
		MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}
	*/

	//set size of window//
	SMALL_RECT srectWin;
	srectWin.Left = 0;
	srectWin.Top = 0;
	srectWin.Right = wd - 1;
	srectWin.Bottom = ht - 1;
	if (!SetConsoleWindowInfo(hOut, TRUE, &srectWin)) {
		MessageBox(NULL, TEXT("SetConsoleWindowInfo"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	return;
}

void HideCursor()
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//-11
	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	CONSOLE_CURSOR_INFO ci;
	if (!GetConsoleCursorInfo(hOut, &ci)) {
		MessageBox(NULL, TEXT("GetConsoleCursorInfo"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	ci.bVisible = FALSE;
	if (!SetConsoleCursorInfo(hOut, &ci)) {
		MessageBox(NULL, TEXT("SetConsoleCursorInfo"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}
	return;
}
