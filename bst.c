/*
**
Created by Andrew Stere for use in Calculon
**
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "value.h"
#include "bst.h"
static void insertNode(node *, node *);

bst *createBST(void) {
  bst *b = (bst *)malloc(sizeof(bst));
  b->head = NULL;
  return b;
}

void insert(bst *b, node *v) {
  if(b->head == NULL) {
    b->head = v;
    return;
  }
  insertNode(b->head,v);
  return;

}
static void insertNode(node *head, node *v) {

  if (strcmp(head->value->sval,v->value->sval) > 0) {
    if(head->left == NULL)
      head->left = v;
    else
      insertNode(head->left, v);

  }
  else if (strcmp(head->value->sval, v->value->sval) < 0) {
    if (head->right == NULL)
      head->right = v;
    else
      insertNode(head->right, v);
  }
  else
    head->next = v->next;
}

value * findVal(node *bs, value *v) {
  if(bs == NULL) {
    return NULL;
  }

  if (strcmp(v->sval,bs->value->sval) > 0){
    return findVal(bs->right,v);
  }
  else if (strcmp(v->sval,bs->value->sval) < 0) {
    return findVal(bs->left,v);
  }
  else {
    return bs->next->value;
  }
}
