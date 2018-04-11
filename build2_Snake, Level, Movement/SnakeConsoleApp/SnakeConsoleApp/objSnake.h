#ifndef OBJSNAKE_H
#define OBJSNAKE_H

#include <Windows.h>

struct SNAKE
{
	SHORT x;
	SHORT y;
	CHAR direction;
	DWORD speed;
};

static const DWORD MAX_SPEED = 10;

static SNAKE snake;

static DWORD spd_count = 0;

#endif
