/**
@file Queue.h
@author Rob Thomas
@brief Contains code for the operations of a queue data structure.
@details Contains a Queue struct and functions for initializing, destroying,
enqueueing, and dequeueing.
*/

#ifndef QUEUE_H
#define QUEUE_H

/*** INCLUDES: ***/

#include <stdbool.h>



/*** DEFINES: ***/
/**
@def Q_RESIZED
@brief Info code indicating that a Queue struct was resized during enqueueing or
dequeueing. Does NOT indicate that the operation failed.
*/
#define Q_RESIZED 20
/**
@def Q_LOOPED
@brief Info code indicating that a Queue struct of fixed size looped around 
itself during enqueueing or dequeueing such as a circular queue would.
Does NOT indicate that the operation failed.
*/
#define Q_LOOPED 21

/**
@def Q_EMPTY_QUEUE_FAIL
@brief Error code signifying that the user attempted to dequeue from an empty
queue.
*/
#define Q_EMPTY_QUEUE_FAIL -400



/*** STRUCTS: ***/

/**
@typedef Queue
@brief A struct that represents a simple queue data structure. Items inside of
this queue are stored as simple bytes. If the queue is of fixed size, then it 
will behave like a circular queue, erasing the oldest items when attempting to
enqueue over capacity.
@var QueueSize The size of the queue in number of items that COULD be stored.
@var NumItems The number of items currently stored in this queue.
@var ItemSize The size (in bytes) of each item in this queue.
@var SizeIsFixed Boolean variable indicating whether or not this queue is of 
fixed size or variable size. If false, this queue will automatically resize 
itself when adding items beyond its capacity or when less than a fourth of the
capacity is being used.
@var Top The index (in Items) of the top item of the queue. This is the item 
that will be returned by dequeueing.
@var Bottom The index in Items of the slot that is to be filled with an item
next.
@var Items The list of items inside of this queue. This is where data of items
is stored.
*/
typedef struct 
{
	unsigned int QueueSize;
	unsigned int NumItems;
	size_t ItemSize;

	bool SizeIsFixed;

	unsigned int Top;
	unsigned int Bottom;

	void **Items;
} Queue;



/*** FUNCTION PROTOTYPES: ***/

/**
@fn Q_Init
@brief Initializes a Queue struct with the given starting size (in items)
and item size (in bytes). This queue is dynamically allocated and 
*MUST BE FREED* using Q_Free once no longer necessary.
@param startSize The number of items that the queue will be allocated for. 
@param itemSize The size (in bytes) of the type of item that will be stored in
this queue.
@param isFixedSize True if this queue will be of fixed size. False if the queue
will be allowed to automatically resize itself during enqueueing or dequeueing.
@return A pointer to a newly allocated Queue struct. NULL if a problem was 
encountered.
*/
Queue *Q_Init (unsigned int startSize, unsigned int itemSize, bool isFixedSize);

/**
@fn Q_Free
@brief Deconstructs a Queue and frees its dynamically allocated members.
This Queue can no longer be accessed after this function is called.
@param queue Pointer to the Queue struct to be freed.
*/
void Q_Free (Queue *queue);

/**
@fn Q_enqueue
@brief Adds an item to the given queue.
@param queue Pointer to the Queue which the item will be placed into.
@param item Void pointer which points to the item to be added.
@return An error code. 0 if no problems were encountered.
*/
int Q_enqueue (Queue *queue, void *item);

/**
@fn Q_dequeue
@brief Removes and returns the top item inside of the given queue.
@param queue Pointer to the Queue struct which will return an item.
@param buffer Pointer to where the item (which is a collection of bits) will be 
stored.
@return An error code. 0 if no problems were encountered.
*/
int Q_dequeue (Queue *queue, void *buffer);

#endif /* QUEUE_H */