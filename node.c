/*
**
Created by Andrew Stere for use in Calculon
**
*/
#include <stdio.h>
#include <stdlib.h>
#include "value.h"
#include "node.h"

node *init(value *v) {
    node *temp = (node *)malloc(sizeof(node));
    temp->value = v;
    temp->next = NULL;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node *initBST(value *var, value *val) {
    node *temp = (node *)malloc(sizeof(node));
    temp->value = var;
    temp->next = init(val);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
