#pragma once
#include <iostream>

#define TERMS 5
#define NONTERMS 3

enum OPTYPE {turn_left, turn_right, move, aim, shoot, prog3, prog2, iflookingat, last};

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

