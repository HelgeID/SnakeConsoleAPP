#ifndef ENGINE_H
#define ENGINE_H

#include <Windows.h>

CHAR keyboardCheckPressed();
void playSound(const DWORD);
void inKey(const DWORD);

//keys
//...

//additional functions
void GoToXY(const SHORT, const SHORT);
void SetColor(const DWORD);
void Print(const LPSTR);

#endif
