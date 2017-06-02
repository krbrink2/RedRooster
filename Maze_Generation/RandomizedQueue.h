/**
@file RandomizedQueue.h
@author Rob Thomas
@brief Contains code for the operations of a randomized queue.
@details Contains a RandomQueue struct and helped functions for such a queue's
initialization, operations, maintenance, and destruction. The queue is 
dynamically allocated and has variable size.
*/

#ifndef RANDOMIZED_QUEUE_H
#define RANDOMIZED_QUEUE_H

/*** INCLUDES: ***/

#include <stdbool.h>



/*** DEFINES: ***/
/**
@def RQ_RESIZED
@brief Info code indicating that a random queue was resized while enqueueing or
dequeueing. This does NOT mean that an error occurred during the operation.
*/
#define RQ_RESIZED 500

/**
@def RQ_INSUFFICIENT_SIZE_FAIL
@brief Error code signifying that an item couldn't be added to a RandomQueue 
because it was at capacity and was of fixed size.
*/
#define RQ_INSUFFICIENT_SIZE_FAIL -500
/**
@def RQ_EMPTY_QUEUE_FAIL
@brief Error code signifying that dequeueing failed due to an empty queue.
*/
#define RQ_EMPTY_QUEUE_FAIL -501



/*** STRUCTS: ***/

/**
@typedef RandomQueue
@brief This struct is used to represent a randomized queue.
@var QueueSize The current size of the queue in number of items that COULD be 
stored (not necessarily ARE stored).
@var NumItems The number of items currently inside of the queue.
@var ItemSize The size (in bytes) of each item inside of the queue.
@var SizeIsFixed Boolean variable indicating whether or not this queue is of 
fixed size or variable size. If false, this queue will automatically resize 
itself when adding items beyond its capacity or when less than a fourth of the
capacity is being used.
@var Items The list of items inside of this queue. This is where data of items
is stored.
*/
typedef struct 
{
	unsigned int QueueSize;
	unsigned int NumItems;
	size_t ItemSize;

	bool SizeIsFixed;

	void **Items;
} RandomQueue;



/*** FUNCTION PROTOTYPES: ***/

/**
@fn RQ_Init
@brief Initializes a RandomQueue struct with the given starting size (in items)
and item size (in bytes). This queue is dynamically allocated and 
*MUST BE FREED* using RQ_Free once no longer necessary.
@param startSize The number of items that the queue will be allocated for. 
@param itemSize The size (in bytes) of the type of item that will be stored in
this queue.
@param isFixedSize True if this queue will be of fixed size. False if the queue
will be allowed to automatically resize itself during enqueueing or dequeueing.
@return A pointer to a newly allocated RandomQueue struct. NULL if a problem
was encountered.
*/
RandomQueue *RQ_Init (unsigned int startSize, unsigned int itemSize,
					  bool isFixedSize);

/**
@fn RQ_Free
@brief Deconstructs a RandomQueue and frees its dynamically allocated members.
This RandomQueue can no longer be accessed after this function is called.
@param queue Pointer to the RandomQueue struct to be freed.
*/
void RQ_Free (RandomQueue *queue);

/**
@fn RQ_enqueue
@brief Adds an item to the given queue.
@param queue Pointer to the RandomQueue which the item will be placed into.
@param item Void pointer which points to the item to be added.
@return An error code. 0 if no problems were encountered.
*/
int RQ_enqueue (RandomQueue *queue, void *item);

/**
@fn RQ_dequeue
@brief Removes and returns a random item inside of the given queue.
@param queue Pointer to the RandomQueue struct which will return an item.
@param buffer Pointer to where the item (which is a void pointer) will be 
stored.
@return An error code. 0 if no problems were encountered.
*/
int RQ_dequeue (RandomQueue *queue, void *buffer);

#endif /* RANDOMIZED_QUEUE_H */