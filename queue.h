#ifndef QUEUE_H
#define QUEUE_H

#include "def.h"

struct Queue
{
    int head, tail, capacity;
    Str20 *array;
};

struct Queue *createQueue(int size);
bool queueEmpty(struct Queue *queue);
bool queueFull(struct Queue *queue);
void enQueue(struct Queue *queue, Str20 elem);
void deQueue(struct Queue *queue, Str20 str);
void head(struct Queue *queue, Str20 str);
void freeQueue(struct Queue *queue);

#endif