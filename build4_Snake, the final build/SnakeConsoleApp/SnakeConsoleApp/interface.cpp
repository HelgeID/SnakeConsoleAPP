#include "interface.h"
#include "engine.h"
#include "colors.h"
#include "resource.h"
#include <stdlib.h>//for system("cls");

#define szGameOver "GAME OVER"
#define szBack "Press Enter to back to main memu"

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
	WORD cStart(cGOLD), cExit(cWHITE), cAbout(cWHITE);//init colors
	system("cls");

	//init arguments//
	bKey = ' ';
	gameOver = FALSE;
	closeConsole = FALSE;
	
	while (!gameOver && !closeConsole)
	{
		while (bKey != VK_RETURN)
		{
			//Start
			SetColor(cStart); GoToXY(37, 18); Print("START");
			//Exit
			SetColor(cExit);  GoToXY(37, 20); Print("EXIT");
			//About
			SetColor(cAbout);  GoToXY(37, 22); Print("ABOUT");

			bKey = keyboardCheckPressed();
			if (bKey == 'w' && choise == 2) {
				//active START
				choise--; cStart = cGOLD; cExit = cWHITE; cAbout = cWHITE;
				playSound(szClick);
			}
			else if (bKey == 'w' && choise == 3) {
				//active EXIT
				choise--; cStart = cWHITE; cExit = cGOLD; cAbout = cWHITE;
				playSound(szClick);
			}
			else if (bKey == 's' && choise == 1) {
				//active EXIT
				choise++; cStart = cWHITE; cExit = cGOLD; cAbout = cWHITE;
				playSound(szClick);
			}
			else if (bKey == 's' && choise == 2) {
				//active ABOUT
				choise++; cStart = cWHITE; cExit = cWHITE; cAbout = cGOLD;
				playSound(szClick);
			}
		}

		switch (choise) {
		case 1: {
			playSound(szClick);
			gameOver = TRUE;
		}; break;
		case 2: {
			closeConsole = TRUE;
		}; break;
		case 3: {
			playSound(szClick);
			AboutMenu(bKey);
		}; break;
		default: break;
		}

		system("cls");//clear the console
		bKey = ' ';//clear the variable to the entered character
	}

	return;
}

void AboutMenu(CHAR& bKey)
{
	DWORD szClick(IDR_WAVE1);
	system("cls");

	SetColor(cGOLD);
	Print('\n', 6);
	Print(' ', 37); Print("SNAKE\n\n");
	Print(' ', 15); Print("This just a simple snake game demo written in C++.\n");
	Print(' ', 30); Print("Rules are very clear:\n");
	Print(' ', 20); Print("If a snake will touch bordes - game over.\n");
	Print(' ', 17); Print("If a snake will bite it's own tail - game over.\n");
	Print(' ', 9); Print("The snake must eat some fruits for becoming bigger and faster.\n");
	Print(' ', 18); Print("By each eaten fruit you will get some scores.\n\n");

	Print(' ', 7); Print("Controls:\n");
	Print(' ', 15); Print("Use the <A>, <D>, <W>, <S> keys for moving a snake.\n\n");

	Print(' ', 7); Print("Programming:\n");
	Print(' ', 15); Print("       \n\n");
	Print(' ', 18); Print("Thanks to the YouTube channel                \n");
	Print(' ', 24); Print("for the snake in pure assembler.\n\n");

	Print(' ', 7); Print("Music:\n");
	Print(' ', 15); Print("Spineless\n\n");

	SetColor(cDARK_RED);
	GoToXY(15, 19); Print("HelgeID");
	GoToXY(48, 21); Print("Tempesta Torres");

	inKey(cDARK_RED);
	playSound(szClick);

	return;
}

void GameOverMenu(CHAR& bKey)
{
	SHORT goY(1);
	SHORT bY(41);

	const SHORT center(19);
	DWORD szClick(IDR_WAVE1);
	DWORD szLose(IDR_WAVE3);

	//music
	StopMusic();
	
	//cleaning screen
	system("cls");

	SetColor(cDARK_RED);
	playSound(szLose);

	while (bKey != VK_RETURN) {
		GoToXY(35, ++goY); Print(szGameOver);
		GoToXY(35, goY - 1); Print(' ', 9);
		GoToXY(24, --bY); Print(szBack);
		GoToXY(24, bY + 1); Print(' ', 32);
		Sleep(200);
		if (goY < center)
			;
		else {
			SetColor(cRED);
			GoToXY(35, goY); Print(szGameOver);
			GoToXY(24, bY); Print(szBack);
	checkKey:
			bKey = keyboardCheckPressed();
			if (bKey != VK_RETURN)
				goto checkKey;
			else
				playSound(szClick);
		}
	}

	//music
	CloseMusic();

	return;
}
