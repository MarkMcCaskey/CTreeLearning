//import relevant files
#include <stdio.h>  //printing
#include <stdlib.h> //various utility
#include <time.h>   //for setting the random seed

//macro, replaced at compile time
#define TREE_SIZE 100
#define VALUE_RANGE 1000

//binary tree
struct tree
{
	struct tree* left;
	struct tree* right;
	int value;
};
/*
 * Structs are like arrays but with arbitrary types
 * Elements are laid out in order in memory
a*
 * access struct elements with:
 * .  normal
 * -> pointer
 *
 * i.e. 
 * struct tree* t; t->left->value;
 * struct tree t; t.left->value;
 */


int main( void );
struct tree* generateTree( void );
int* treeToArray( struct tree * );
void insert( struct tree*, int );
void deleteTree( struct tree* );


int main( void )
{
	srandom( time( NULL ) ); //seed the random number generator with the time
	struct tree* t = generateTree(); //create new tree with random numbers
	int* array = treeToArray( t ); //change tree into array and store it in array
	
	//loop through all elements in array and print them
	int i;
	for( i = 0; i < TREE_SIZE; ++i )
	{
		printf( "%d ", *(array + i) );
	}
	
	//free allocated memory
	deleteTree( t ); //recursively free nodes in tree
	free( array ); //free entire block allocated for array
	
	exit( EXIT_SUCCESS );
}

struct tree* generateTree( void )
{
	//allocate memory on the heap for the root node
	struct tree* t = (struct tree *) malloc( sizeof( struct tree ) );
	//check for proper allocation
	if( t == NULL )
	{
		//report error and terminate program if memory cannot be allocated
		fprintf( stderr, "Failed to allocate memory for root node.\n" );
		exit( EXIT_FAILURE );
	}

	//set first value of root node
	t->value = random() % VALUE_RANGE ;

	//insert up to 99 random numbers into the tree
	int i;
	for( i = 0; i < TREE_SIZE - 1; ++i )
	{
		insert( t, random() % VALUE_RANGE );
	}
	return t;
}

//puts elements into tree in a sorted order
//ignores duplicates
void insert( struct tree* t, int v )
{
	if( v == t-> value )
		return; //ignore non-unique values

	//if new value is larger than current value
	if( v > t->value )
	{
		//and the right node is not empty
		if( t->right != NULL )
		{
			//recursively search through the tree
			insert( t->right, v );
			return;
		}
		//else t->right is NULL
		t->right = malloc( sizeof( struct tree ) );
		//once the correct place has been found place the value in the
		// node
		t->right->value = v;
		return;

	} else { //v < t->value
        //if value was not >= to v then it must be less than 
		if( t->left != NULL )
		{
			//recursively find correct node
			insert( t->left, v );
			return;
		}
		//else t->left is NULL
		t->left = malloc( sizeof( struct tree ) );
		//place value in correct node
		t->left->value = v;
		return;
	}

}

int* treeToArray( struct tree * t )
{
	/*
	 * Write your code here
	 * 
	 * Tree is layed out like this:
	 *         6
	 *       /   \
	 *      3     8
	 *     / \   / \
	 *    2   4 7   10
	 *
	 *
	 * populate array in sorted order and return it
	 */
	
	int* ip = (int *) malloc( sizeof( int ) * TREE_SIZE );
	
	/*
	 * add elements to array either by using *(ip + offset) = value;
	 * or by using ip[offset] = value;
	 */
	
	//return pointer to block of memory allocated earlier in function
	return ip;
}

/* Recursively free all nodes in tree
 *
 * This function has no return value, it mutates the data at the location
 * specified by the pointer struct tree* t
 */
void deleteTree( struct tree* t )
{
	//search right until NULL is found
	if( t->right != NULL )
	{
		deleteTree( t->right );
	} 
	//search left until NULL is found
	if( t->left != NULL )
	{
		deleteTree( t->left );
	} 
	//once both right and left are NULL delete node
	free( t );
}
