#ifndef ENGINE_H
#define ENGINE_H

#include <Windows.h>

#define MAX_STEP 40

static DWORD nLevel = 1;
static DWORD score = 0;

#define STOP '0'

//draw functions
void DrawLevel();
void DrawSnake(SHORT, SHORT);
void DrawScore();
void DrawPanel();

//game functions
void GameInit();
void GameUpdate();
void GameController(CHAR&, BOOL&, BOOL&);

//controller functions
void EventKey(CHAR&, BOOL&, BOOL&);
void EventDraw();
void EventStep(CHAR&, BOOL&, BOOL&);

CHAR keyboardCheck();
CHAR keyboardCheckPressed();
void playSound(const DWORD);
void inKey(const DWORD);
CHAR CheckPosition(const SHORT, const SHORT);

//keys
//...

//additional functions
void GoToXY(const SHORT, const SHORT);
void SetColor(const WORD);
void Print(const LPSTR);

#endif
