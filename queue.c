/*
**
Created by Andrew Stere for use in Calculon
**
*/
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "value.h"
#include "queue.h"

Queue *createQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enQueue(Queue *q, value *v)
{
    node *temp = init(v);
    if (q->front == NULL)
    {
       q->front = temp;
       q->rear = temp;
       return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

value *deQueue(Queue *q)
{
    if (q->front == NULL)
    {
      return NULL;
    }

    node *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
    {
       q->rear = NULL;
    }
    return temp->value;
}
