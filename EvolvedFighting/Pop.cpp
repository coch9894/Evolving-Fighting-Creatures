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
		population[count] = NULL;
	}
	
	for( int count = 0; count < POP_SIZE; count++ )
	{
		char* str;
		std::queue<node*> q;

		str = new char[10];
		i.getline(str,10);

		if( str[0] == '\n' && count < POP_SIZE )
		{
			char temp;
			std::cout << "Error in loading population" << std::endl;
			std::cin >> temp;
			exit(-1);
		}

		while( str[0] != '8' )
		{
			node * temp;
			temp = new node();

			switch( str[0] )
			{
			case turn_left:
				temp->type = turn_left;
				break;
			case turn_right:
				temp->type =  turn_right;
				break;
			case move:
				temp->type = move;
				break;
			case aim:
				temp->type = aim;
				break;
			case shoot:
				temp->type = shoot;
				break;
			case prog3:
				temp->type = prog3;
				break;
			case prog2:
				temp->type = prog2;
				break;
			case iflookingat:
				temp->type = iflookingat;
				break;
			}

			q.push(temp);

			i.getline(str,10);
		}

		population[count] = q.front();
		population[count]->parent = NULL;
		q.pop();

		node * temp = population[count];
		std::queue<node*> fill;
		fill.push(temp);

		while( !fill.empty() )
		{
			temp = fill.front();
			fill.pop();

			temp->left = q.front();
			temp->left->parent = temp;
			q.pop();
			if( temp->left != NULL )
			{
				fill.push(temp->left);
			}

			if( temp->type == prog3 )
			{
				temp->mid = q.front();
				temp->mid->parent = temp;
				q.pop();
				if( temp->mid != NULL )
				{
					fill.push(temp->mid);
				}
			}

			temp->right = q.front();
			temp->right->parent = temp;
			q.pop();
			if( temp->right != NULL )
			{
				fill.push(temp->right);
			}
		}

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