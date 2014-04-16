#pragma once

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

class Pop
{
public:
	Pop(void);
	~Pop(void);
};

