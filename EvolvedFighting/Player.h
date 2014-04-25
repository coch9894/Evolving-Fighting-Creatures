#pragma once
#include "node.h"
#include "Bullet.h"

class Player
{
public:
	Player(void);
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

	void DrawPlayer();

	int GetSize() { return root->GetSize(); }

	node *GetRoot();
	void SetRoot(node *);

	node *root;

private:
	int y_pos;	//in pixels
	int x_pos;	//in pixels

	float direction; //the angle

	int numHits;	//number of times being hit
};

