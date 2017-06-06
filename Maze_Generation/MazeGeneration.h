/**
@file MazeGeneration.h
@author Rob Thomas
@brief Contains code for the procedural generation of simple 2D mazes. 
*/

/*** INCLUDES: ***/

#include <stdbool.h>

/*** DEFINES: ***/

#define FAULTY_DEQUEUE_RESULT_FAIL -1000

/*** STRUCTS: ***/

/**
@typedef Space
@brief Struct representing a single space in a maze.
@var rightWall True if this space has a wall on its right side. False otherwise.
@var bottomWall True if this space has a wall on its bottom side. False
     otherwise.
@var visited True if this space has been visited by a branch. False otherwise.
*/
typedef struct 
{
	bool rightWall;
	bool bottomWall;
	bool visited;
} Space;

/**
@typedef Maze
@brief Struct representing a rectangular 2D maze.
@var width The width (in spaces) of the maze.
@var height The height (in spaces) of the maze.
@var array An array of spaces representing the maze itself. In array[x][y],
     x gives the row desired and y gives the column desired.
*/
typedef struct 
{
	int width;
	int height;

	Space **array;
} Maze;

/**
@typedef Branch
@brief Struct representing a single branch exploring the maze. At any time, 
       several branches may be exploring the maze concurrently.
@var name The name of the branch. A branch's name is equivalent to the name of 
     the branch that spawned it with a single letter appended which indicated
     which child this is. For instance, if the initial branch is named "A", then
     its first child will be named "AA" and its second child will be named "AB".
     Then, that branch's first child will be named "ABA" and its second child
     will be named "ABB", and so on. The name is purely cosmetic.
@var row The row of the space that this branch is currently in.
@var col The column of the space that this branch is currently in.
@var letterOffset An offset indicating the letter to be appended to this 
     branch's next child branch. A letterOffset of 0 means the next child's name
     will be this branch's name with an 'A' appended, and a letterOffset of 2
     means a 'C' will be appended instead.
*/
typedef struct
{
	char *name;

	int row;
	int col;
	int letterOffset;
} Branch;

/**
@typedef MazeTemplate
@brief A struct that houses settings for how the maze should be generated and
       how likely certain events are.
@var branchGenThreshold An array dictating the likelihood of a new branch being
     generated by an old branch that has just moved to a new space. 
     branchGenThreshold[0] gives the likelihood of one branch being generated.
     branchGenThreshold[1] gives the likelihood of a second branch being 
     generated.
     branchGenThreshold[2] gives the likelihood of a third branch being 
     generated.
     As these represent probabilities, each should be between 0 and 1 
     (inclusive).
@var moveUpMod The probability of any branch to move upwards.
@var moveDownMod The probabily of any branch to move downwards.
@var moveLeftMod The probability of any branch to move to the left.
@var moveRightMod The probability of any branch to the move to the right.
@var universalLoopChance The probability of any branch to create a loop at any
     point where it has moved next to a visited space separated by a wall.
@var terminationLoopChance The probability of a branch that has run out of 
     places to move to create a loop.
@var minLoopDistance The minimum distance between two spaces for a loop to be
     created between those spaces.
*/
typedef struct 
{
	float branchGenThreshold[3];

	float moveUpMod;
	float moveDownMod;
	float moveLeftMod;
	float moveRightMod;
	float universalLoopChance;
	float terminationLoopChance;

	int minLoopDistance;
} MazeTemplate;

/**
@typedef SearchPoint
@brief A struct representing a single space in the maze. Used for determing the
       shortest distance in the maze between two spaces.
@var row Row index of the space in the maze.
@var col Column index of the space in the maze.
@var prevSpace Integer indicating which space was searched that lead to this
     space being searched. (1 => space above, 2 => space below, etc)
@var pathLength Distance of this space from the space where the search started.
*/
typedef struct 
{
	int row;
	int col;
	int prevSpace;
	int pathLength;
} SearchPoint;

/*** FUNCTION PROTOTYPES: ***/

/**
@fn buildMaze
@brief Procedurally generates a maze using the given parameters.
@param maze Pointer to an initialized Maze struct.
@param template An initialized MazeTemplate struct which contains the various
                parameters for the maze's construction, particularly modifiers
                to the probabilities of various paths. 
*/
void buildMaze (Maze *maze, MazeTemplate template);

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
	                Branch *branch);

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
	             int row, int col, int targetRow, int targetCol);

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
void getNeighbors (Maze *maze, RandomizedQueue *RQ, int row, int col);

/**
@fn genProbability
@brief Generates a uniformly distributed random float between 0 and 1 (inclusive). 
       This float can be compared against thresholds to see if a random event 
       should occur or not.
@return A random float between 0 and 1.
*/
float genProbability ();

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
	               int row, int col, int targetRow, int targetCol);

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
int wallBetween (Maze *maze, int Arow, int Acol, int Brow, int Bcol);

/**
@fn removeWallBetween
@brief Removes a wall existing between two adjacent spaces.
@param maze Pointer to the current Maze struct.
@param row Row index of the first space.
@param col Column index of the first space.
@param nextRow Row index of the second space.
@param nextCol Column index of the second space.
*/
void removeWallBetween (Maze *maze, int row, int col, int nextRow, int nextCol);