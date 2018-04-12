#ifndef OBJFRUIT_H
#define OBJFRUIT_H

#include <Windows.h>

#define TIME_BLINK 8

struct FRUIT
{
	SHORT x;
	SHORT y;
	DWORD sprite;
};

static FRUIT fruit;
static DWORD blink;

#endif
