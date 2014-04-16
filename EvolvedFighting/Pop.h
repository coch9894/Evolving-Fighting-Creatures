#pragma once

#include "Player.h"
#include "Bullet.h"

typedef enum Terms
{
	Forward,
	Left,
	Right,
	Shoot,
	Backward,
	DoNothing,
	Aim
}Terms;

typedef enum NonTerms
{
	prog2,
	prog3,
	ifhit,
	ifinsight
}NonTerms;

#define TERMS 7
#define NONTERMS 4

class Pop
{
public:
	Pop(void);
	~Pop(void);
};

