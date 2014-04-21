#include "Pop.h"
#include <queue>

Pop::Pop(void)
{
}


Pop::~Pop(void)
{
}



void Pop::load_pop(void)
{
	std::ifstream i;
	i.open("init.dat");

	for( int count = 0; count < POP_SIZE; count++ )
	{
		delete population[count];
	}
	
	for( int count = 0; count < POP_SIZE; count++ )
	{
		std::string str;
	}
}

void Pop::write_pop(void)
{
	std::ofstream o;
	o.open( "init.dat" );
	
	for( int count = 0; count < POP_SIZE; count++ )
	{
		population[count] = new node();
		population[count]->generate(DEPTH,NULL,root);
	}

	for( int count = 0; count < POP_SIZE; count++ )
	{
		std::queue<node*> q;
		
		q.push(population[count]);

		while( !q.empty() )
		{
			node * temp;
			temp = q.front();
			q.pop();

			if( temp->left != NULL )
			{
				q.push(temp->left);
			}
			if( temp->mid != NULL )
			{
				q.push(temp->mid);
			}
			if( temp->right != NULL )
			{
				q.push(temp->right);
			}

			switch( temp->type )
			{
			case turn_left:
				o << "0\n";
				break;
			case turn_right:
				o << "1\n";
				break;
			case move:
				o << "2\n";
				break;
			case aim:
				o << "3\n";
				break;
			case shoot:
				o << "4\n";
				break;
			case prog3:
				o << "5\n";
				break;
			case prog2:
				o << "6\n";
				break;
			case iflookingat:
				o << "7\n";
				break;
			}
		}

		// end of the tree print separating char
		o << "8\n";
	}
}