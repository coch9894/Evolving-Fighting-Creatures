#pragma once
#include "node.h"
#include "Bullet.h"
#include <math.h>

#define _USE_MATH_DEFINES

//enum OPTYPE {turn_left, turn_right, move, aim, shoot, prog3, prog2, last};

#define BASE_ANGLE 15
#define RADIUS 5

class Player
{
public:
	Player(void);
	Player(int, int);
	~Player(void);

	void TurnLeft();	//rotate counter-clockwise
	void TurnRight();	//rotate clockwise
	void MoveForward();	//move in the direction we're facing

	void Aim();	//shoots faster?

	void Shoot();	//fires a bullet

	bool IsHit(Bullet *);

	void Evaluate();

	int getNumHits();	// number of times this player got hit

	int getFitness();	//should get the number of times opposing player got hit

	void Normalize_Fitness(void);

	void DrawPlayer();

	int GetSize() { return root->GetSize(); }

	node *GetRoot();
	void SetRoot(node *);

	node *root;

private:
	//maybe public?
	double fitness;	//normalized fitness only for selecting an elite
					//very important to keep this straight

	int y_pos;	//in pixels
	int x_pos;	//in pixels
	float speed;	//initialized to some constant possible #DEFINE

	float direction; //the angle in degrees

	float numSuccess;	//number of times hitting opponent
	float numFail;	//number of times being hit
};

