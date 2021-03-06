#ifndef _PLAYER_H
#define _PLAYER_H

#include "node.h"
#include "util.h"
#include <stack>

#define _USE_MATH_DEFINES

//enum OPTYPE {turn_left, turn_right, move, aim, shoot, prog3, prog2, last};

#define BASE_ANGLE 3.14159/6
#define DEPTH 3


class Player
{
public:
	Player(void);
	Player(bool);
	~Player(void);

	void TurnLeft();	//rotate counter-clockwise
	void TurnRight();	//rotate clockwise
	void MoveForward();	//move in the direction we're facing

	void Aim();	//shoots faster?

	//void Shoot(int);	//fires a bullet

	void GotHit()	{ numFail++; }
	void Hit()	{ numSuccess++; }

	void Evaluate();

	int getNumHits();	// number of times this player got hit

	double getFitness();	//should get the number of times opposing player got hit

	void Normalize_Fitness(void);
	void Evaluate_Fitness(int);
	void MaxMax(void);
	void MinMax(void);
	void MinMin(void);
	void MaxMin(void);

	void DrawPlayer(int);

	int GetSize() { return root->GetSize(); }

	node *GetRoot() { return this->root; }
	void SetRoot(node *n) { this->root = n; }

	double GetDirection() { return this->direction; }
	void SetDirection(double a) { this->direction = a; }

	int GetY() { return this->y_pos; }
	int GetX() { return this->x_pos; }

	void SetY(int y) { this->y_pos = y; }
	void SetX(int x) { this->x_pos = x; }

	void SetSuccess(float s) { this->numSuccess = s; }
	float GetSuccess() { return this->numSuccess; }
	void SetFail(float f) { this->numFail = f; }
	float GetFail() { return this->numFail; }

	double GetTrainingFitness() { return this->training_fitness; }

	void mutate();

	node *root;

	int totalBullets;
	int Team;

private:
	//maybe public?
	double fitness;	//normalized fitness only for selecting an elite
					//very important to keep this straight
	double training_fitness;

	int y_pos;	//in pixels
	int x_pos;	//in pixels
	double speed;	//initialized to some constant possible #DEFINE

	double direction; //the angle in degrees

	float numSuccess;	//number of times hitting opponent
	float numFail;	//number of times being hit
};

#endif

