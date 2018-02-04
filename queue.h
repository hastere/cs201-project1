/*
**
Created by Andrew Stere for use in Calculon
**
*/
#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"
#include "value.h"

typedef struct queueObject
{
    node *front;
    node *rear;
} Queue;

extern Queue *createQueue();
extern void enQueue(Queue *q, value *v);
extern value *deQueue(Queue *q);

#endif
