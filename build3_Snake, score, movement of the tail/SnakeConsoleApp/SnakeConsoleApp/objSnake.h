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

struct TAIL
{
	SHORT x;
	SHORT y;
};

static const DWORD MAX_SPEED = 10;
static const DWORD MAX_TAIL = 500;

static SNAKE snake;
static TAIL tail[MAX_TAIL];

static DWORD spd_count = 0;
static DWORD nTail = 0;

#endif
