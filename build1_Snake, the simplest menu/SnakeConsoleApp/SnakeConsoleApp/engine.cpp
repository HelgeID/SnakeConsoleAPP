#include "engine.h"
#include <conio.h>

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

void SetColor(const DWORD color)
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
