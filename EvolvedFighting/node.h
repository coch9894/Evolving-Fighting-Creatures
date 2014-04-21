#pragma once
#include <iostream>

enum OPTYPE {turn_left, turn_right, move, aim, prog3, prog2, iflookingat, last};

enum NODELOC {root, nleft, nmid, nright};

class node
{
private:
public:
	NODELOC loc;
	OPTYPE type;
	node *left;
	node *mid;
	node *right;

	node *parent;

	node(void);
	~node(void);
	void generate(int, node*, NODELOC l = root);
	void mutate();
	node * copyTree(node *, node *);
	node * GetSubTree(int);

	int GetSize();

	void PrintTree(node *);

};

