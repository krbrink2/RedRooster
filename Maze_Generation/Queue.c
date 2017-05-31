/**
@file Queue.h
@author Rob Thomas
@brief Contains code for the operations of a queue data structure.
@details Contains a Queue struct and functions for initializing, destroying,
enqueueing, and dequeueing.
*/

/*** INCLUDES: ***/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Queue.h"


/*** FUNCTION DEFINITIONS: ***/

int main (int argc, char *argv[])
{
	int result = -1;

	/* Test a basic queue by adding the numbers 1 through 10 then dequeueing 
	   them. */
	Queue *queue = Q_Init(16, sizeof(int), true);

	for ( int i = 1; i <= 32; i++ )
	{
		result = Q_enqueue(queue, &i);
		if ( result < 0 )
		{
			fprintf(stderr, "Error #%d encountered.\n", result);
		}

		printf("Item #%d enqueued.", i);
		if ( result == Q_RESIZED )
		{
			printf("\t+++(%d / %d)+++\n", queue->NumItems, queue->QueueSize);
		}
		else
		{
			printf("\t(%d / %d)\t", queue->NumItems, queue->QueueSize);

			if ( result == Q_LOOPED )
			{
				printf("!LOOPED!");
			}

			puts("");
		}
	}

	puts("\nEnqueueing complete.\n");

	/* Dequeue each item. */
	int buffer = 0;

	while ( queue->NumItems > 0 )
	{
		result = Q_dequeue(queue, &buffer);
		if ( result < 0 )
		{
			fprintf(stderr, "Error #%d encountered.\n", result);
		}

		printf("Item #%d dequeued.", buffer);
		if ( result == Q_RESIZED )
		{
			printf("\t---(%d / %d)---\n", queue->NumItems, queue->QueueSize);
		}
		else
		{
			printf("\t(%d / %d)", queue->NumItems, queue->QueueSize);

			if ( result == Q_LOOPED )
			{
				printf("!LOOPED!");
			}

			puts("");
		}
	}

	result = Q_dequeue(queue, &buffer);

	if ( result < 0 )
	{
		fprintf(stderr, "Error %d encountered.\n", result);
	}
	else
	{
		printf("Code #%d encountered.\n", result);
	}

	return 0;
}

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
Queue *Q_Init (unsigned int startSize, unsigned int itemSize, bool isFixedSize)
{
	/*** Allocate a new Queue struct. ***/
	Queue *queue = (Queue *)malloc( sizeof(Queue) );

	/*** Set the data members of this Queue based on the given parameters. ***/
	queue->ItemSize = itemSize;
	queue->SizeIsFixed = isFixedSize;
	queue->QueueSize = startSize;
	queue->Top = 0;
	queue->Bottom = 0;

	/*** Allocate this queue's list of items. ***/
	queue->Items = (void **)malloc( sizeof(void *) * startSize );

	/*** Allocate each empty item in the list. ***/
	for (int i = 0; i < startSize; i++)
	{
		queue->Items[i] = malloc( itemSize );
	}

	return queue;
}

/**
@fn Q_Free
@brief Deconstructs a Queue and frees its dynamically allocated members.
This Queue can no longer be accessed after this function is called.
@param queue Pointer to the Queue struct to be freed.
*/
void Q_Free (Queue *queue)
{
	/*** Free each item in this queue's list. ***/
	for (int i = queue->Top; i < queue->QueueSize; i++)
	{
		free(queue->Items[i]);
	}

	/*** Free the queue's list of items. ***/
	free(queue->Items);

	/*** Free the queue itself. ***/
	free(queue);
}

/**
@fn Q_enqueue
@brief Adds an item to the given queue.
@param queue Pointer to the Queue which the item will be placed into.
@param item Void pointer which points to the item to be added.
@return An error code. 0 if no problems were encountered.
*/
int Q_enqueue (Queue *queue, void *item)
{
	bool resized = false;
	bool looped = false;

	/*** If the queue is at max capacity and is NOT of fixed size, double its
	     amount of allocated space. ***/
	if ( !queue->SizeIsFixed )
	{
		int originalSize = queue->QueueSize;

		while ( queue->QueueSize <= queue->NumItems )
		{
			/* If the queue's size is zero, set it to one now. */
			if ( queue->QueueSize < 1 )
			{
				queue->QueueSize = 1;
				break;
			}

			/* Otherwise, double the queue's size. */
			queue->QueueSize *= 2;
		}

		if ( queue->QueueSize != originalSize )
		{
			/* Reallocate the list of items for the new size. */
			queue->Items = (void **)realloc( queue->Items, 
						sizeof(void *) * queue->QueueSize );

			/* Allocate for the new items. */
			for ( int i = originalSize; i < queue->QueueSize; i++ )
			{
				queue->Items[i] = malloc( queue->ItemSize );
			}

			/* Record that the queue was resized. */
			resized = true;
		}
	}

	/*** Save the new item at the bottom pointer. ***/
	memcpy(queue->Items[queue->Bottom], item, queue->ItemSize);

	/*** Increment the number of items in this queue. ***/
	(queue->NumItems)++;

	/*** Increment the bottom of the queue. ***/
	(queue->Bottom)++;

	/*** If the queue is at capacity and is of fixed size, loop the bottom 
	     pointer (where the next item will be placed) around to the top of the 
	     queue. ***/
	if ( queue->SizeIsFixed )
	{
		if ( queue->Bottom >= queue->QueueSize )
		{
			queue->Bottom %= queue->QueueSize;

			looped = true;
		}

		if ( queue->NumItems > queue->QueueSize )
		{
			queue->NumItems = queue->QueueSize;

			if ( queue->Top < queue->Bottom )
			{
				/* Advance the top to point to the next item. */
				queue->Top = queue->Bottom;
			}
		}

		if ( looped )
		{
			/* Notify the user that the queue's bottom pointer looped around. */
			return Q_LOOPED;
		}
	}
	else if ( resized )
	{
		return Q_RESIZED;
	}

	return 0;
}

/**
@fn Q_dequeue
@brief Removes and returns the top item inside of the given queue.
@param queue Pointer to the Queue struct which will return an item.
@param buffer Pointer to where the item (which is a collection of bits) will be 
stored.
@return An error code. 0 if no problems were encountered.
*/
int Q_dequeue (Queue *queue, void *buffer)
{
	bool resized = false;

	/*** If there are no items in this queue, notify the user and exit. ***/
	if ( queue->NumItems <= 0 )
	{
		return Q_EMPTY_QUEUE_FAIL;
	}

	/*** Copy the item pointed to by the top pointer into the buffer. ***/
	memcpy(buffer, queue->Items[queue->Top], queue->ItemSize);

	/*** Increment the queue's top pointer. ***/
	(queue->Top)++;

	/*** Decrement the number of items in this queue. ***/
	(queue->NumItems)--;

	/*** If this queue is of fixed size, loop the top pointer around if it now
	     exceeds the size of the queue. ***/
	if ( queue->SizeIsFixed && queue->Top >= queue->QueueSize )
	{
		queue->Top %= queue->QueueSize;

		return Q_LOOPED;
	}

	/*** If this queue is not of fixed size and now occupies less than one 
	     fourth of the space allocated for it, halve the amount of space 
	     allocated for it. ***/
	else if ( !queue->SizeIsFixed )
	{
		while ( queue->NumItems * 4 < queue->QueueSize )
		{
			int originalSize = queue->QueueSize;

			/* Halve this queue's size. */
			queue->QueueSize /= 2;

			/* Allocate a block of memory matching the new size of the queue. */
			void **ItemsBuffer = (void **)calloc( queue->QueueSize, 
								  sizeof(void *) );

			/* Allocate for each of the items */
			for (int i = 0; i < queue->QueueSize; i++)
			{
				ItemsBuffer[i] = malloc( queue->ItemSize );
			}

			/* Copy the items from the queue into this block of memory. */
			for (int i = 0; i < queue->NumItems; i++)
			{
				memcpy(ItemsBuffer[i], queue->Items[queue->Top + i], 
					   queue->ItemSize);
			}

			/* Update this queue's top and bottom index to match with the new
			   array of items. */
			queue->Top = 0;
			queue->Bottom = queue->NumItems;

			/* Replace the queue's list of items with the newly constructed
			   list. */
			for (int i = 0; i < originalSize; i++)
			{
				free(queue->Items[i]);
			}

			free(queue->Items);

			queue->Items = ItemsBuffer;

			/* Record that the queue was resized. */
			resized = true;

			/* If the number of items is 0 and the queue's size has been 
			   reduced down to 1, do not let it be reduced all the way to 0. */
			if ( queue->QueueSize == 1 )
			{
				break;
			}
		}
	}

	if ( resized )
	{
		return Q_RESIZED;
	}

	return 0;
}