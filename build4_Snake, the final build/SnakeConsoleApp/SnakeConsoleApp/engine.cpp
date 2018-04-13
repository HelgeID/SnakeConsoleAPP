#include "engine.h"
#include "colors.h"
#include "objFruit.h"
#include "objSnake.h"
#include <conio.h>
#include <stdio.h>
#include "resource.h"

#include <time.h>//for RangedRandFruit()

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

void DrawPanel()
{
	const WORD cPanel(48);
	SetColor(cPanel);
	GoToXY(21, 37);
	Print("Esc - back to menu, P - pause the game");

	return;
}

void CreateScore()
{
	SetColor(cGREEN);
	GoToXY(1, 37);
	Print("Score: 0");
	(score != 0) ? score = 0 : NULL;
	(score_old != 0) ? score_old = 0 : NULL;

	return;
}

void DrawScore()
{
	if (score > score_old) {
		SetColor(cGREEN);
		GoToXY(8, 37);
		CHAR buff[10];
		sprintf_s(buff, "%d", score);
		LPSTR s_score = const_cast<LPSTR>(buff);
		Print(s_score);
		score_old = score;
	}

	return;
}

//objSnake functions
void CreateSnake()
{
	//snake
	snake.x = 40;
	snake.y = 20;
	snake.direction = ' ';
	snake.speed = MAX_SPEED;

	spd_count = 0;

	//tail
	ClearTail();
	nTail = 0;
	nPickup = 0;

	return;
}

void DrawSnake(SHORT x, SHORT y)
{
	GoToXY(x, y);
	SetColor(cCYAN);
	putchar('O');

	return;
}

void DrawTail()
{
	SetColor(cCYAN);
	int index(0);
	for (;;) {
		if (tail[index].x == 0 || tail[index].y == 0)
			break;
		GoToXY(tail[index].x, tail[index].y);
		putchar('o');

		if (!(++index < nTail))
			break;
	}

	return;
}

void ClearTail()
{
	int index(0);
	for (;;) {
		tail[index].x = 0;
		tail[index].y = 0;

		if (!(++index < nTail))
			break;
	}

	return;
}

//objFruit functions
void CreateFruit()
{
	SHORT xFruit(0), yFruit(0);
	while (TRUE) {
		RangedRandFruit(xFruit, yFruit);
		if (CheckPosition(xFruit, yFruit) == ' ')
			break;
	}
	
	fruit.x = xFruit;
	fruit.y = yFruit;
	fruit.sprite = 1;
	blink = 0;

	return;
}

void DrawFruit()
{
	blink++;
	if (blink >= TIME_BLINK) {
		if (fruit.sprite == 1)
			fruit.sprite = 2;
		else
			fruit.sprite = 1;
		blink = 0;
	}
	GoToXY(fruit.x, fruit.y);
	SetColor(cRED);
	putchar(fruit.sprite);

	return;
}

void RangedRandFruit(SHORT& x, SHORT& y)
{
	srand((unsigned)time(NULL));
	const SHORT MinX(1), MaxX(80);
	const SHORT MinY(1), MaxY(35);
	x = MinX + rand() % (MaxX - MinX + 1);
	y = MinY + rand() % (MaxY - MinY + 1);

	return;
}

//game functions
void GameInit()
{
	DrawLevel();
	DrawPanel();

	//init score//
	CreateScore();

	//init snake//
	CreateSnake();
	
	//init fruit//
	CreateFruit();

	//init music//
	CreateMusic();

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

		//check tail
		if (nTail > 0) {
			SHORT x_prev(tail->x), y_prev(tail->y);//save the 0 element of the tail
			(*tail).x = x;//tail = head(X)
			(*tail).y = y;//tail = head(Y)
			GoToXY(x_prev, y_prev);
			putchar(' ');

			SHORT x_temp, y_temp;
			int index(1);//next
			for (;;) {
				//save old coordinates
				x_temp = tail[index].x;
				y_temp = tail[index].y;
				GoToXY(x_temp, y_temp);
				putchar(' ');
				//assign the new coordinates
				tail[index].x = x_prev;
				tail[index].y = y_prev;
				//assign the previous coordinates
				x_prev = x_temp;
				y_prev = y_temp;

				if (!(++index < nTail))
					break;
			}
		}

		//erase the previous position of the snake
		GoToXY(snake.x, snake.y);
		putchar(' ');

		if (snake.direction == 'w') {
			y--;
			if (CheckPosition(x, y) == ' ' || CheckPosition(x, y) == fruit.sprite)
				snake.y--;
			else if (CheckPosition(x, y) == '#')
				snake.direction = STOP;
		} else
		if (snake.direction == 's') {
			y++;
			if (CheckPosition(x, y) == ' ' || CheckPosition(x, y) == fruit.sprite)
				snake.y++;
			else if (CheckPosition(x, y) == '#')
				snake.direction = STOP;
		} else
		if (snake.direction == 'a') {
			x--;
			if (CheckPosition(x, y) == ' ' || CheckPosition(x, y) == fruit.sprite)
				snake.x--;
			else if (CheckPosition(x, y) == '#')
				snake.direction = STOP;
		} else
		if (snake.direction == 'd') {
			x++;
			if (CheckPosition(x, y) == ' ' || CheckPosition(x, y) == fruit.sprite)
				snake.x++;
			else if (CheckPosition(x, y) == '#')
				snake.direction = STOP;
		}

		spd_count = 0;
	}

	//catcing a tail
	if (nTail > 0) {
		int index(0);
		for (;;) {
			if (tail[index].x == snake.x && tail[index].y == snake.y)
				snake.direction = STOP;

			if (!(++index < nTail))
				break;
		}
	}

	//catcing a fruit
	if ((snake.x == fruit.x) &&
		(snake.y == fruit.y)) {
		//add tail
		if (nTail < MAX_TAIL) {
			CreateFruit();

			nTail++;
			nPickup++;
			score+=10;

			DWORD szTreasure(IDR_WAVE2);
			playSound(szTreasure);
		}
	}
	
	//speed test
	if (nPickup == SPD_STEP) {
		nPickup = 0;
		snake.speed--;
		if (snake.speed <= 0) {
			snake.speed = MAX_SPEED;
		}
	}

	return;
}

void GameController(CHAR& bKey, BOOL& gameOver, BOOL& closeConsole)
{
	EventKey(bKey, gameOver, closeConsole);
	EventDraw();
	EventStep(bKey, gameOver, closeConsole);
	EventMusic();

	return;
}

void GamePause(CHAR& bKey)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//-11
	if (hOut == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
		exit(EXIT_FAILURE);
	}

	PauseMusic();

	while (TRUE) {
		SetColor(cWHITE); GoToXY(37, 18); Print("PAUSE");
		Sleep(500);//ms

		SetColor(cGOLD); GoToXY(37, 18); Print("PAUSE");
		Sleep(500);//ms

		bKey = keyboardCheck();
		if (bKey == 'p') {
			GoToXY(37, 18);
			Print("     ");
			goto exit;
		}
	}
exit:
	PlayMusic();

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
		GamePause(bKey);
	else if (bKey == 'w' || bKey == 's' || bKey == 'a' || bKey == 'd')
		snake.direction = bKey;

	return;
}

void EventDraw()
{
	if (nTail > 0)
		DrawTail();

	DrawSnake(snake.x, snake.y);

	DrawFruit();

	DrawScore();

	return;
}

void EventStep(CHAR& bKey, BOOL& gameOver, BOOL& closeConsole)
{
	if (snake.direction == STOP)
		gameOver = FALSE;

	Sleep(MAX_STEP);

	return;
}

void EventMusic()
{
	if (mPlay == FALSE)
		PlayMusic();

	if (!isPlayingMusic() && mPlay) {
		CloseMusic();

		//new
		CreateMusic();
	}

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

void Print(const CHAR ch, WORD length)
{
	for (int i=0; i<length; i++)
		putchar(ch);

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

void inKey(const WORD color)
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

//music functions
void CreateMusic()
{
	if (!mInit) {
		LPCSTR szBuff("open music\\music.mid type sequencer alias MUSIC_SND");
		mciSendString(szBuff, NULL, 0, NULL);
		mInit = TRUE;
		mPlay = FALSE;
	}
	return;
}

void PlayMusic()
{
	if (mInit && !mPlay) {
		LPCSTR szBuff("play MUSIC_SND notify");
		mciSendString(szBuff, NULL, 0, NULL);
		mPlay = TRUE;
	}
	return;
}

void PauseMusic()
{
	if (mInit && mPlay) {
		LPCSTR szBuff("pause MUSIC_SND notify");
		mciSendString(szBuff, NULL, 0, NULL);
		mPlay = FALSE;
	}
	return;
}

void StopMusic()
{
	if (mInit && mPlay) {
		LPCSTR szBuff;
		szBuff = "stop MUSIC_SND";
		mciSendString(szBuff, NULL, 0, NULL);
		szBuff = "seek MUSIC_SND to start";
		mciSendString(szBuff, NULL, 0, NULL);
		mPlay = FALSE;
	}
	return;
}

void CloseMusic()
{
	if (mInit) {
		LPCSTR szBuff("close all");
		mciSendString(szBuff, NULL, 0, NULL);
		mInit = FALSE;
		mPlay = FALSE;
	}
	return;
}

BOOL isPlayingMusic()
{
	CHAR value[32];
	const CHAR pl[] = "playing";
	mciSendString("status MUSIC_SND mode", value, 32, NULL);
	if (!_stricmp(value, pl))
		return TRUE;
	return FALSE;
}
