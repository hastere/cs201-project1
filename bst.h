/*
**
Created by Andrew Stere for use in Calculon
**
*/
#ifndef BST_H
#define BST_H

#include "value.h"
#include "node.h"

typedef struct bst {
  node *head;
} bst;

bst *createBST(void);
void insert(bst *, node *);
value *findVal(node *, value *);

#endif
