#ifndef QUEUE_C
#define QUEUE_C

#define QUEUE_OVERFLOW_ERROR 12
#define QUEUE_UNDERFLOW_ERROR 13 // adjust if need be

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"

// LINEAR IMPLEMENTATION

struct Queue *createQueue(int size)
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->capacity = size;
    queue->head = -1; // init both to -1 = empty
    queue->tail = -1;
    queue->array = (Str20 *)malloc(queue->capacity * sizeof(Str20));
    return queue;
}

bool queueEmpty(struct Queue *queue)
{
    return queue->head == -1 && queue->tail == -1;
}

bool queueFull(struct Queue *queue)
{
    return queue->tail == queue->capacity - 1;
}

void enQueue(struct Queue *queue, Str20 elem)
{
    if (queueFull(queue))
    {
        printf("ERROR: QUEUE OVERFLOW\n");
        exit(QUEUE_OVERFLOW_ERROR);
    }
    if (queueEmpty(queue))
        queue->head = 0;

    // increment tail then add item
    strcpy(queue->array[++queue->tail], elem);
}

void deQueue(struct Queue *queue, Str20 str)
{
    if (queueEmpty(queue))
    {
        printf("ERROR: QUEUE UNDERFLOW\n");
        exit(QUEUE_UNDERFLOW_ERROR);
    }

    strcpy(str, queue->array[queue->head]); // get head (erm)
    if (queue->head == queue->tail)         // set to empty
        queue->head = queue->tail = -1;
    else // move head index up
        queue->head++;
}

void head(struct Queue *queue, Str20 str)
{
    if (!queueEmpty(queue))
        strcpy(str, queue->array[queue->head]);
}

void freeQueue(struct Queue *queue)
{
    free(queue->array);
    free(queue);
}

#endif