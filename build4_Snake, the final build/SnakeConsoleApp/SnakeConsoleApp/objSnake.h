#ifndef OBJSNAKE_H
#define OBJSNAKE_H

#include <Windows.h>

#define MAX_SPEED 10	//max speed of the snake
#define SPD_STEP 3		//step of the speed
#define MAX_TAIL 500	//max length of the tail

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

static SNAKE snake;
static TAIL tail[MAX_TAIL];

static DWORD spd_count = 0;
static WORD nTail = 0;
static DWORD nPickup = 0;

#endif
