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
@fn iterateBranch
@brief Moves a branch to a single unvisited neighboring space, then checks if
       new branches should be spawned from the branch's starting space.
@param maze Pointer to the current Maze struct.
@param template The MazeTemplate struct defining attributes of the maze.
@param queue Pointer to the Queue of branches.
@param branch Pointer to the branch to be iterated on (the last branch to be
       dequeued from queue).
*/
void iterateBranch (Maze *maze, MazeTemplate template, Queue *queue, 
	                Branch *branch)
{
	/* Get a list in randomized order of all of the current space's unvisited
	   neighbors. */
	RandomizedQueue *RQ = RQ_Init(4, sizeof(int), false);
	getNeighbors(maze, RQ, branch->row, branch->col);
	/* If there are no unvisited neighbors, this branch has reached an end.
	   Check if any loops should be formed. */
	if ( RQ->NumItems >= 0 )
	{
		/* Try forming a loop to the space above. */
		if ( branch->row > 0 && wallBetween(maze, branch->row, branch->col, 
			                                branch->row - 1, branch->col) )
		{
			tryGenerateLoop(maze, template, branch->row, branch->col, 
				            branch->row - 1, branch->col);
		}
		/* Try forming a loop to the space below. */
		if ( branch->row < maze->height - 1 && 
			 wallBetween(maze, template, branch->row, branch->col, 
			             branch->row - 1, branch->col) )
		{
			tryGenerateLoop(maze, template branch->row, branch->col, 
				            branch->row + 1, branch->col);
		}
		/* Try forming a loop to the space to the left. */
		if ( branch->col > 0 && wallBetween(maze, branch->row, branch->col, 
			                                branch->row, branch->col - 1) )
		{
			tryGenerateLoop(maze, template, branch->row, branch->col, 
				            branch->row, branch->col - 1);
		}
		/* Try forming a loop to the space to the right. */
		if ( branch->col < maze->width - 1 && 
			 wallBetween(maze, branch->row, branch->col, 
			             branch->row, branch->col + 1) )
		{
			tryGenerateLoop(maze, template, branch->row, branch->col, 
							branch->row, branch->col + 1);
		}
		/* Since the branch has ended, it must also be freed. */
		free(branch->name);
		free(branch);
	}
	/* If there is at least one unvisited neighbor, choose one to go to. */
	else
	{
		int nextSpace, oldRow, oldCol;
		oldRow = branch->row;
		oldCol = branch->col;
		RQ_dequeue(RQ, &nextSpace);
		switch (nextSpace)
		{
			/* Move to top neighbor. */
			case 1:
				removeWallBetween(maze, branch->row, branch->col, 
					              branch->row - 1, branch->col);
				branch->row -= 1;
				maze->array[branch->row][branch->col].visited = true;
				break;
			/* Move to the bottom neighbor. */
			case 2:
				removeWallBetween(maze, branch->row, branch->col, 
					              branch->row + 1, branch->col);
				branch->row += 1;
				maze->array[branch->row][branch->col].visited = true;
				break;
			/* Move to the left neighbor. */
			case 3:
				removeWallBetween(maze, branch->row, branch->col, 
					              branch->row, branch->col - 1);
				branch->col -= 1;
				maze->array[branch->row][branch->col].visited = true;
				break;
			/* Move to the right neighbor. */
			case 4:
				removeWallBetween(maze, branch->row, branch->col, 
					              branch->row, branch->col + 1);
				branch->col += 1;
				maze->array[branch->row][branch->col].visited = true;
				break;
		}
		/* Put the branch back into the queue. */
		Q_enqueue(queue, &branch);
		/* Attempt to generate new branches. */
		genBranches(maze, template, queue, branch, oldRow, oldCol, branch->row,
			        branch->col);
	}
	RQ_free(RQ);
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
	p /= float(RAND_MAX);
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
@fn wallBetween
@brief Determines if there is a wall between the two given spaces and, if so, 
where the second space is relative to the first (above, below, etc).
@param maze Pointer to the current Maze struct.
@param Arow Row index of the first space.
@param Acol Column index of the first space.
@param Brow Row index of the second space.
@param Bcol Column index of the second space.
@return 1 if space B is directly above A and a wall is between them.
		2 if space B is directly below A and a wall is between them.
		3 if space B is directly to the left of A and a wall is between them.
		4 if space B is directly to the right of A and a wall is between them.
		0 otherwise.
*/
int wallBetween (Maze *maze, int Arow, int Acol, int Brow, int Bcol)
{
	if ( Acol == Bcol )
	{
		/* Check for B directly above A. */
		if ( Arow == Brow + 1 )
		{
			if ( maze->array[Brow][Bcol].bottomWall )
			{
				return 1;
			}
		}
		/* Check for B directly below A. */
		else if ( Arow == Brow - 1 )
		{
			if ( maze->array[Arow][Acol].bottomWall )
			{
				return 2;
			}
		}
	}
	else if ( Arow == Brow )
	{
		/* Check for B directly to the left of A. */
		if ( Acol == Bcol + 1 )
		{
			if ( maze->array[Brow][Bcol].rightWall )
			{
				return 3;
			}
		}
		/* Check for B directly to the right of A. */
		else if ( Acol == Bcol - 1 )
		{
			if ( maze->array[Arow][Acol].rightWall )
			{
				return 4;
			}
		}
	}
	return 0;
}

/**
@fn removeWallBetween
@brief Removes a wall existing between two adjacent spaces.
@param maze Pointer to the current Maze struct.
@param row Row index of the first space.
@param col Column index of the first space.
@param nextRow Row index of the second space.
@param nextCol Column index of the second space.
*/
void removeWallBetween (Maze *maze, int row, int col, int nextRow, int nextCol)
{
	/* Determine where the first space is relative to the second. */
	int W = wallBetween(maze, row, col, nextRow, nextCol);

	switch (W)
	{
		/* B above A. */
		case 1: 
			maze->array[Brow][Bcol].bottomWall = false;
			break;
		/* B below A. */
		case 2:
			maze->array[Arow][Acol].bottomWall = false;
			break;
		/* B to the left of A. */
		case 3:
			maze->array[Brow][Bcol].rightWall = false;
			break;
		/* B to the right of A. */
		case 4:
			maze->array[Arow][Acol].rightWall = false;
			break;
		/* Otherwise, do nothing. */
		default:
	}
}

