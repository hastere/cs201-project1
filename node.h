/*
**
Created by Andrew Stere for use in Calculon
**
*/

#ifndef NODE_H
#define NODE_H

#include "value.h"

typedef struct node
  {
  value *value;
  struct node *next;
  struct node *left;
  struct node *right;
} node;

extern node *init(value *);
extern node *initBST(value *, value *);
#endif
