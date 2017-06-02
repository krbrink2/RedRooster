/**
@file RandomizedQueue.c
@author Rob Thomas
@brief Contains code for the operations of a randomized queue.
@details Contains a RandomQueue struct and helped functions for such a queue's
initialization, operations, maintenance, and destruction. The queue is 
dynamically allocated and has variable size. All items inside the queue are 
stored as void pointers, allowing the queue to handle any type of data. One 
queue may only store one data type.
*/


/*** INCLUDES: ***/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "RandomizedQueue.h"


/*** FUNCTION DEFINITIONS: ***/

int main (int argc, char *argv[])
{
	/*** Test case: Add numbers 1-10 to a random queue, then dequeue all of
	     them to ensure randomness. ***/
	int result;
	RandomQueue *queue = RQ_Init(1, sizeof(int), false);

	for (int i = 1; i <= 10; i++)
	{
		result = RQ_enqueue(queue, &i);

		if ( result < 0 )
		{
			fprintf(stderr, "Error #%d encountered.\n", result);
		}

		printf("Item #%d enqueued.", i);
		if ( result == RQ_RESIZED )
		{
			printf("\t+++(%d / %d)+++\n", queue->NumItems, queue->QueueSize);
		}
		else
		{
			printf("\t(%d / %d)\n", queue->NumItems, queue->QueueSize);
		}
	}

	puts("\nEnqueues complete.\n");

	int X = -1;

	while ( queue->NumItems > 0 )
	{
		result = RQ_dequeue(queue, &X);

		if ( result < 0 )
		{
			fprintf(stderr, "Error #%d encountered.\n", result);
		}

		printf("Item #%d dequeued.", X);
		if ( result == RQ_RESIZED )
		{
			printf("\t---(%d / %d)---\n", queue->NumItems, queue->QueueSize);
		}
		else
		{
			printf("\t(%d / %d)\n", queue->NumItems, queue->QueueSize);
		}
	}

	return 0;
}

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
					  bool isFixedSize)
{
	/*** Allocate the RandomQueue struct. ***/
	RandomQueue *queue = (RandomQueue *)malloc( sizeof(RandomQueue) );

	/*** Set each of its data members based on the parameters passed in. ***/
	queue->QueueSize = startSize;
	queue->ItemSize = itemSize;
	queue->NumItems = 0;
	queue->SizeIsFixed = isFixedSize;

	/*** Allocate the RandomQueue's list of items. ***/
	queue->Items = (void **)malloc( sizeof(void *) * startSize );

	/*** Allocate each item in the list of items. ***/
	for (int i = 0; i < startSize; i++)
	{
		queue->Items[i] = malloc( itemSize );
	}

	/*** Return the allocated struct pointer. ***/
	return queue;
}

/**
@fn RQ_Free
@brief Deconstructs a RandomQueue and frees its dynamically allocated members.
This RandomQueue can no longer be accessed after this function is called.
@param queue Pointer to the RandomQueue struct to be freed.
*/
void RQ_Free (RandomQueue *queue)
{
	/*** Free each item in the queue's list. ***/
	for (int i = 0; i < queue->QueueSize; i++)
	{
		free(queue->Items[i]);
	}

	/*** Free the queue's list. ***/
	free(queue->Items);

	/*** Free the RandomQueue itself. ***/
	free(queue);
}

/**
@fn RQ_enqueue
@brief Adds an item to the given queue.
@param queue Pointer to the RandomQueue which the item will be placed into.
@param item Void pointer which points to the item to be added.
@return An error code. 0 if no problems were encountered.
*/
int RQ_enqueue (RandomQueue *queue, void *item)
{
	bool resized = false;

	/*** If this queue is not of fixed size, check if its size needs to be
	     increased to fit a new item. ***/
	if ( !queue->SizeIsFixed )
	{
		/* If the queue isn't large enough to fit another item, allocate more
		   memory for it. */
		while ( queue->QueueSize <= queue->NumItems )
		{
			queue->QueueSize *= 2;

			/* If a queue has non-positive size, set its size to 1 so that it
			   doesn't simply resize infinitely. */
			if ( queue->QueueSize < 1 )
			{
				queue->QueueSize = 1;
			}

			queue->Items = (void **)realloc( queue->Items, 
							    sizeof(void *) * queue->QueueSize );

			/* Allocate for the new empty items. */
			if ( queue->QueueSize == 1 )
			{
				queue->Items[0] = malloc( queue->ItemSize );
			}
			else
			{
				for ( int i = queue->QueueSize / 2; i < queue->QueueSize; i++ )
				{
					queue->Items[i] = malloc( queue->ItemSize );
				}
			}

			resized = true;
		}
	}

	/*** If this queue is of fixed size and there is no more room for new items,
	     report this to the user. ***/
	else if ( queue->QueueSize <= queue->NumItems )
	{
		return RQ_INSUFFICIENT_SIZE_FAIL;
	}

	/*** Copy the new item into the queue. ***/
	memcpy( queue->Items[queue->NumItems], item, queue->ItemSize );

	/*** Increment the number of items in the queue. ***/
	(queue->NumItems)++;

	/*** If the queue was resized during the process, report this to the 
	     user. ***/
	if ( resized )
	{
		return RQ_RESIZED;
	}

	return 0;
}

/**
@fn RQ_dequeue
@brief Removes and returns a random item inside of the given queue.
@param queue Pointer to the RandomQueue struct which will return an item.
@param buffer Pointer to where the item (which is a void pointer) will be 
stored.
@return An error code. 0 if no problems were encountered.
*/
int RQ_dequeue (RandomQueue *queue, void *buffer)
{
	bool resized = false;

	/*** Make sure there are items in this queue that can be dequeued. ***/
	if ( queue->NumItems < 1 )
	{
		return RQ_EMPTY_QUEUE_FAIL;
	}

	/*** Choose a random item in the queue to remove and return. ***/
		/* Seed the random number generator. */
	srand(time(NULL));
		/* The random number must be between the index of the first item (0) and
		   the index of the last item (NumItems - 1). */
	int index = rand() % queue->NumItems;

	/*** Store this item inside of the buffer. ***/
	memcpy(buffer, queue->Items[index], queue->ItemSize);

	/*** Swap the chosen item with the last item in the queue. ***/
	void *swappedItem = queue->Items[index];
	queue->Items[index] = queue->Items[queue->NumItems - 1];
	queue->Items[queue->NumItems - 1] = swappedItem;

	/*** Decrement the number of items. ***/
	(queue->NumItems)--;

	/*** If the queue is not of fixed size and now occupies less than one fourth 
		 of the space allocated for it, halve its allocated space. ***/
	if ( !queue->SizeIsFixed )
	{
		bool noItems = false;

		while ( queue->NumItems * 4 < queue->QueueSize && !noItems )
		{
			int initialSize = queue->QueueSize;

			/* Halve the queue's size. */
			queue->QueueSize /= 2;

			/* If the queue's number of items is 0, set its size to 1. */
			if ( queue->NumItems < 1 )
			{
				queue->QueueSize = 1;

				noItems = true;
			}

			/* Before resizing, free all of the items that have just been 
			   erased. */
			for ( int i = queue->QueueSize; i < initialSize; i++ )
			{
				free( queue->Items[i] );
			}

			/* Reallocate the list of items. */
			queue->Items = (void **)realloc( queue->Items, 
							sizeof(void *) * queue->QueueSize );

			/* Record that the queue has been resized. */
			resized = true;
		}
	}

	if ( resized )
	{
		return RQ_RESIZED;
	}

	return 0;
}