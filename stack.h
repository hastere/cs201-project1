/*
**
Created by Andrew Stere for use in Calculon
**
*/
#ifndef STACK_H
#define STACK_H

#include "value.h"
#include "node.h"

typedef struct Stack
{
    node *rear;
} Stack;

extern Stack *createStack();
extern void push(Stack *s, value *v);
extern value *pop(Stack *s);
#endif
