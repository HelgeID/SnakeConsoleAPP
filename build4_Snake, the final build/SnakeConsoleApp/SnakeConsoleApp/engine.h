#ifndef ENGINE_H
#define ENGINE_H

#include <Windows.h>

#define MAX_STEP 30

static DWORD nLevel = 1;
static DWORD score = 0;
static DWORD score_old = 0;

#define STOP '0'

static BOOL mInit = FALSE;
static BOOL mPlay = FALSE;

//draw functions
void DrawLevel();
void DrawPanel();

void CreateScore();
void DrawScore();

//objSnake functions
void CreateSnake();
void DrawSnake(SHORT, SHORT);
void DrawTail();
void ClearTail();

//objFruit functions
void CreateFruit();
void DrawFruit();
void RangedRandFruit(SHORT&, SHORT&);

//game functions
void GameInit();
void GameUpdate();
void GameController(CHAR&, BOOL&, BOOL&);
void GamePause(CHAR&);

//controller functions
void EventKey(CHAR&, BOOL&, BOOL&);
void EventDraw();
void EventStep(CHAR&, BOOL&, BOOL&);
void EventMusic();

CHAR keyboardCheck();
CHAR keyboardCheckPressed();
void playSound(const DWORD);
void inKey(const WORD);
CHAR CheckPosition(const SHORT, const SHORT);

//keys
//...

//additional functions
void GoToXY(const SHORT, const SHORT);
void SetColor(const WORD);
void Print(const LPSTR);
void Print(const CHAR, WORD);

//music functions
void CreateMusic();
void PlayMusic();
void PauseMusic();
void StopMusic();
void CloseMusic();
BOOL isPlayingMusic();

#endif
