#include "interface.h"
#include "engine.h"
#include "colors.h"
#include "resource.h"
#include <stdlib.h>//for system("cls");

void MainMenu(HANDLE& hOut, CHAR& bKey, BOOL& gameOver, BOOL& closeConsole)
{
	//get handle//
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//-11
	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	/*test
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	DWORD cWritten;
	WriteFile(hOut, "test", lstrlenA("test"), &cWritten, NULL);

	*/

	DWORD szClick(IDR_WAVE1);

	DWORD choise(1);
	DWORD cStart(cWHITE), cExit(cGOLD);
	system("cls");

	//init arguments//
	bKey = STOP;
	gameOver = FALSE;
	closeConsole = FALSE;
	
	while (!gameOver && !closeConsole)
	{
		while (bKey != VK_RETURN)
		{
			//START
			SetColor(cStart); GoToXY(37, 19); Print("START");
			//EXIT
			SetColor(cExit);  GoToXY(37, 21); Print("EXIT");

			bKey = keyboardCheckPressed();
			if (bKey == 'w' && choise == 2) {
				choise--; cStart = cWHITE; cExit = cGOLD;
				playSound(szClick);
			}
			else if (bKey == 's' && choise == 1) {
				choise++; cStart = cGOLD; cExit = cWHITE;
				playSound(szClick);
			}
		}

		if (choise == 1)
			gameOver = TRUE;
		else if (choise == 2)
			closeConsole = TRUE;

		system("cls");//clear the console
		bKey = STOP;//clear the variable to the entered character
	}

	return;
}
