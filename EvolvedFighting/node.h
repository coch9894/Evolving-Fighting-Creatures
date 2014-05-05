#ifndef _NODE_H
#define _NODE_H
#include <iostream>

#define TERMS 5
#define NONTERMS 2

enum OPTYPE {turn_left, turn_right, move, aim, shoot, prog3, prog2, last};

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

	node(bool);
	node(void);
	~node(void);
	void generate(int, node*, NODELOC l = root);
	void mutate();
	node * copyTree(node *, node *);
	node * GetSubTree(int);

	int GetSize();

	void PrintTree(node *);

};

#endif