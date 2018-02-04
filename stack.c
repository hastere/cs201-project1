/*
**
Created by Andrew Stere for use in Calculon
**
*/
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "value.h"
#include "stack.h"


Stack *createStack(void)
{
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->rear = NULL;
    return s;
}

void push(Stack *s, value *v)
{
    node *temp = init(v);
    if (s->rear == NULL)
    {
       s->rear = temp;
       return;
    }
    temp->next = s->rear;
    s->rear = temp;
}

value *pop(Stack *s)
{
    if (s->rear == NULL)
    {
      return NULL;
    }

    node *temp = s->rear;
    s->rear = s->rear->next;

    return temp->value;
}
