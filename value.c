/*
**
Value class adapted from code given in assignment instructions
Modified by Andrew Stere for use in Calculon
**
*/


#include "value.h"
#include <stdio.h>
#include <stdlib.h>

  extern void Fatal(char *,...);

  static value *newValue(int);



  /**** Public Interface ****/

  int INTEGER = 0;
  int REAL = 1;
  int STRING = 2;
  int VARIABLE = 3;
  int OPERATOR = 4;
  int SEMICOLON = 5;

  value *newValueI(int i)
      {
      value *v = newValue(INTEGER);
      v->ival = i;
      v->type = 0;
      return v;
      }

  value *newValueR(double i)
      {
      value *v = newValue(REAL);
      v->rval = i;
      v->type = 1;
      return v;
      }

  value *newValueS(char *i)
      {
      value *v = newValue(STRING);
      v->sval = i;
      v->type = 2;
      return v;
      }

  value *newValueV(char *i)
      {
      value *v = newValue(VARIABLE);
      v->sval = i;
      v->type = 3;
      return v;
      }

  value *newValueO(char *i)
      {
      value *v = newValue(VARIABLE);
      v->sval = i;
      v->type = 4;
      return v;
      }

  value *newValueE(char *i)
      {
      value *v = newValue(VARIABLE);
      v->sval = i;
      v->type = 5;
      return v;
    }
  // similar implementations for newValueR, newValueS, and newValueV

  /**** Private Interface ****/

  static value *newValue(int t)
      {
      value *v;
      if ((v = malloc(sizeof(value))) == 0)
          Fatal("out of memory\n");
      v->type = t;
      v->ival = 0;
      v->rval = 0;
      v->sval = 0;
      return v;
      }
