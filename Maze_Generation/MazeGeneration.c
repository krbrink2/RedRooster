/**
@file MazeGeneration.c
@author Rob Thomas
@brief Contains code for the procedural generation of simple 2D mazes. 
*/

/*** INCLUDES: ***/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Queue.h"
#include "RandomizedQueue.h"

#include "MazeGeneration.h"

/*** FUNCTION DEFINITIONS: ***/

/**
@fn buildMaze
@brief Procedurally generates a maze using the given parameters.
@param maze Pointer to an initialized Maze struct.
@param template An initialized MazeTemplate struct which contains the various
                parameters for the maze's construction, particularly modifiers
                to the probabilities of various paths. 
*/
void buildMaze (Maze *maze, MazeTemplate template)
{
	/*** REQUIRES IMPLEMENTATION ***/
}

/**
@fn genBranches
@brief Determines how many new branches should be created following an old 
       branch moving into a new space. Any branches created this way will be 
       automatically moved into an unvisited neighboring space and placed into
       the queue of branches.
@param maze Pointer to the current Maze struct.
@param template The MazeTemplate containing this maze's parameters.
@param queue Pointer to the Queue of branches.
@param branch Pointer to the old branch which is being evaluated for spawning
       new branches.
@param row The row that the old branch came from.
@param col The column that the old branch came from.
@param targetRow The row that the old branch has just moved to.
@param targetCol The column that the old branch has just moved to.
@return The number of new branches created (0 through 3) or an error code.
*/
int genBranches (Maze *maze, MazeTemplate template, Queue *queue, Branch *branch, 
	             int row, int col, int targetRow, int targetCol)
{
	/* Assemble a random queue of unvisited neighbors, which will be designated
	   by ints. (0 => top neighbor, 1 => bottom neighbor, 2 => left neighbor,
	             3 => right neighbor) */
	RandomizedQueue *RQ = RQ_init(3, sizeof(int), false);
	getNeighbors(maze, RQ, row, col);

	/* Depending on the number of unvisited neighbors, check how many (if any)
	   new branches should be generated. */
	int numBranches = 0;
	while (RQ->numItems > 0)
	{
		/* Check if a new branch should be generated. */
			/* If not, immediately exit the function. No more branches will be
			   generated. */
		if ( genProbability() >= template.branchGenThreshold[numBranches] )
		{ break; }
			/* If yes, obtain from the random queue the neighbor which the new
			   branch should move into. */
		else
		{
			numBranches++;
			int targetSpace = -1;
			RQ_dequeue(RQ, &targetSpace);
			switch (targetSpace)
			{
				case 0: /* top neighbor */
					addNewBranch(maze, queue, branch, row, col, row - 1, col);
					break;
				case 1: /* bottom neighbor */
					addNewBranch(maze, queue, branch, row, col, row + 1, col);
					break;
				case 2: /* left neighbor */
					addNewBranch(maze, queue, branch, row, col, row, col - 1);
					break;
				case 3: /* right neighbor */
					addNewBranch(maze, queue, branch, row, col, row, col + 1);
					break;
				default:
					targetSpace = FAULTY_DEQUEUE_RESULT_FAIL;
			}

			/* Report any errors that were encountered. */
			if ( targetSpace < 0 )
			{
				numBranches = targetSpace;
				break;
			}
		}
	}

	/* Destroy the random queue and exit. */
	RQ_free(RQ);
	return numBranches;
}

/**
@fn getNeighbors
@brief Assembles a randomized list of unvisited spaces adjacent to the space
       given.
@param maze Pointer to the current Maze struct.
@param RQ Pointer to an initialized RandomizedQueue struct which will store the
       list of unvisited neighbors in randomized order.
       @param row The row of the space whose neighbors are being checked.
       @param col The column of the space whose neighbors are being checked.
*/
void getNeighbors (Maze *maze, RandomizedQueue *RQ, int row, int col)
{
	/* Determine which neighbors are unvisited. */
	int n;
		/* Check top neighbor. */
	if ( row > 0 && !( maze->array[row - 1][col].visited ) )
	{
		n = 0;
		RQ_enqueue(RQ, &n);
	}
	/* Check bottom neighbor. */
	if ( row < maze->height - 1 && !( maze->array[row + 1][col].visited ) )
	{
		n = 1;
		RQ_enqueue(RQ, &n);
	}
	/* Check left neighbor. */
	if ( col > 0 && !( maze->array[row][col - 1].visited ) )
	{
		n = 2;
		RQ_enqueue(RQ, &n);
	}
	/* Check right neighbor. */
	if ( col < maze->width - 1 && !( maze->array[row][col + 1].visited ) )
	{
		n = 3;
		RQ_enqueue(RQ, &n);
	}
}

/**
@fn genProbability
@brief Generates a uniformly distributed random float between 0 and 1 (inclusive). 
       This float can be compared against thresholds to see if a random event 
       should occur or not.
@return A random float between 0 and 1.
*/
float genProbability ()
{
	/* Get a random integer and cast it as a float. */
	float p = float( rand() );
	/* Scale the random float down to between 1 and 0. This produces a random
	   float between 1 and 0 that is uniformly distributed. */
	p /= RAND_MAX;
	return p;
}

/**
@fn addNewBranch
@brief Creates, initializes, and adds a new branch to the queue of branches.
       Also immediately moves this branch into a new space (from the space of 
       the branch's parent.)
@param maze Pointer to the current Maze struct.
@param queue Pointer to the Queue of branches. Must be already initialized.
@param branch Pointer to the old branch which will be spawning a new branch.
@param row The row of the space of the old branch.
@param col The column of the space of the old branch.
@param targetRow The row of the space that the new branch will move into.
@param targetCol The column of the space that the new branch will move into.
*/
void addNewBranch (Maze *maze, Queue *queue, Branch *branch, 
	               int row, int col, int targetRow, int targetCol)
{
	/* Allocate for the new branch. */
	Branch *newBranch = (Branch *)malloc( sizeof(Branch) );
	/* Determine the new branch's name. */
	int nameLength = strlen(branch->name) + 2;
	newBranch->name = (char *)malloc( sizeof(char) * nameLength );
	strcpy(newBranch->name, branch->name);
	newBranch->name[nameLength - 2] = 'A' + branch->branchLetterOffset;
	newBranch->name[nameLength - 1] = '\0';
	branch->branchLetterOffset++;
	/* Set the new branch's other fields. */
	newBranch->branchLetterOffset = 0;
	newBranch->row = targetRow;
	newBranch->col = targetCol;
	/* Add the new branch to the queue of branches. */
	Q_enqueue(queue, &newBranch);
	/* Remove the wall between the start space and the target space. */
	removeWallBetween(maze, row, col, targetRow, targetCol);
	/* Mark the target space as visited. */
	maze->array[targetRow][targetCol].visited = true;
}

/**
*/
void removeWallBetween (Maze *maze, int row, int col, int nextRow, int nextCol)
{
	/*** REQUIRES IMPLEMENTATION ***/
}