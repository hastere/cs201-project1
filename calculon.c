/*
**
Created by Andrew Stere for use in Calculon
**
*/
#include "stack.h"
#include "scanner.h"
#include "bst.h"
#include "queue.h"
#include "node.h"
#include "value.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
/* options */
int postfix = 0;    // option -d
int name = 0;       // option -v
int fileRead = 0;
int lines = 0;
char *author = "Andrew Stere";
char *file = NULL;
bst *b;

//Function decalarations
void ProcessOptions(int,char **);
void Fatal(char *,...);
value *readValue(FILE *);
Queue *readFile(FILE *);
Queue **convertToPost(Queue *);
int priority(value *);
void printQueue(Queue *);
Queue *evaluate(Queue *);
char *concat(value *, value *);
value *performOp(value *, value *, value *);

int main(int argc,char **argv) {
    //Process Options from input
  ProcessOptions(argc,argv);
  b = createBST();

  if (name == 1) {
    printf("%s\n", author);
    return 0;
  }

  FILE *fp = stdin;
  if (fileRead == 1) {
    fp = fopen(file,"r");
    if (fp == NULL) {
      Fatal("Unable to open file for read");
    }
  }

  Queue *q = readFile(fp);
  Queue **q1 = convertToPost(q);

  if (postfix == 1) {
    printQueue(q1[lines - 1]);
    return 0;
  }

  for (int i = 0; i < lines; ++i) {
      q1[i] = evaluate(q1[i]);
  }
  printQueue(q1[lines - 1]);
  return 0;
}

Queue *evaluate(Queue *q) {
  Stack *s = createStack();
  value *v;
  value *opA;
  value *opB;

  while(q->front != NULL) {
    v = deQueue(q);
    if (v->type == 0 || v->type == 1 || v->type == 2 || v->type == 3)
      push(s,v);
    else {
      opB = pop(s);
      opA = pop(s);
      push(s,performOp(v,opA,opB));
    }
  }
  value *temp = pop(s);
  if (temp->type == 3)
    temp = findVal(b->head, temp);
  enQueue(q,temp);
  return q;
}

value *performOp(value *operator, value *opA, value *opB) {
  //assignment operations
  if (operator->sval[0] == '=' && opA->type == 3) {
    node *temp = initBST(opA, opB);
    insert(b, temp);
    return newValueV(opA->sval);
  }
  if(opA->type == 3) {
    opA = findVal(b->head,opA);
    if (opA == NULL)
      Fatal("Variable not found");
  }
  if(opB->type == 3) {
    opB = findVal(b->head,opB);
    if (opB == NULL)
      Fatal("Variable not found");
  }
  //integer operations
  if ( opA->type == 0 && opB->type == 0) {
    if (operator->sval[0] == '+')
      return newValueI((opA->ival + opB->ival));
    else if (operator->sval[0] == '-')
      return newValueI((opA->ival - opB->ival));
    else if (operator->sval[0] == '*')
      return newValueI((opA->ival * opB->ival));
    else if (operator->sval[0] == '/')
      return newValueI((opA->ival / opB->ival));
    else if (operator->sval[0] == '^')
      return newValueI(pow((double)opA->ival,(double)opB->ival));
    else if (operator->sval[0] == '%')
      return newValueI((opA->ival % opB->ival));
  }
  //two doubles operations
  else if ( opA->type == 1 && opB->type == 1) {
    if (operator->sval[0] == '+')
      return newValueR((opA->rval + opB->rval));
    else if (operator->sval[0] == '-')
      return newValueR((opA->rval - opB->rval));
    else if (operator->sval[0] == '*')
      return newValueR((opA->rval * opB->rval));
    else if (operator->sval[0] == '/')
      return newValueR((opA->rval / opB->rval));
    else if (operator->sval[0] == '^')
      return newValueR(pow(opA->rval,opB->rval));
    else if (operator->sval[0] == '%')
      return newValueR(fmod(opA->rval,opB->rval));
  }
  //opA is a double, opB is an int
  else if (opA->type == 1 && opB->type == 0) {
    if (operator->sval[0] == '+')
      return newValueR((opA->rval + (double)opB->ival));
    else if (operator->sval[0] == '-')
      return newValueR((opA->rval - (double)opB->ival));
    else if (operator->sval[0] == '*')
      return newValueR((opA->rval * (double)opB->ival));
    else if (operator->sval[0] == '/')
      return newValueR((opA->rval / (double)opB->ival));
    else if (operator->sval[0] == '^')
      return newValueR(pow(opA->rval,(double)opB->ival));
    else if (operator->sval[0] == '%')
      return newValueR(fmod(opA->rval,(double)opB->ival));
  }
  //opA is an int, opB is a double
  else if (opA->type == 0 && opB->type == 1) {
    if (operator->sval[0] == '+')
      return newValueR(((double)opA->ival + opB->rval));
    else if (operator->sval[0] == '-')
      return newValueR(((double)opA->ival - opB->rval));
    else if (operator->sval[0] == '*')
      return newValueR(((double)opA->ival * opB->rval));
    else if (operator->sval[0] == '/')
      return newValueR(((double)opA->ival / opB->rval));
    else if (operator->sval[0] == '^')
      return newValueR(pow((double)opA->ival,opB->rval));
    else if (operator->sval[0] == '%')
      return newValueR(fmod((double)opA->ival,opB->rval));
  }
  //opA is a string, opB is a double
  else if (opA->type == 2 && opB->type == 1) {\
    if (operator->sval[0] == '+')
      return newValueR((atof(opA->sval) + opB->rval));
    else if (operator->sval[0] == '-')
      return newValueR((atof(opA->sval) - opB->rval));
    else if (operator->sval[0] == '*')
      return newValueR((atof(opA->sval) * opB->rval));
    else if (operator->sval[0] == '/')
      return newValueR((atof(opA->sval) / opB->rval));
    else if (operator->sval[0] == '^')
      return newValueR(pow(atof(opA->sval),opB->rval));
    else if (operator->sval[0] == '%')
      return newValueR(fmod(atof(opA->sval),opB->rval));
  }
  //opA is a string, opB is an int
  else if (opA->type == 2 && opB->type == 0) {
    if (operator->sval[0] == '+')
      return newValueI((atoi(opA->sval) + opB->ival));
    else if (operator->sval[0] == '-')
      return newValueI((atoi(opA->sval) - opB->ival));
    else if (operator->sval[0] == '*')
      return newValueI((atoi(opA->sval) * opB->ival));
    else if (operator->sval[0] == '/')
      return newValueI((atoi(opA->sval) / opB->ival));
    else if (operator->sval[0] == '^')
      return newValueI((atoi(opA->sval) ^ opB->ival));
    else if (operator->sval[0] == '%')
      return newValueI((atoi(opA->sval) % opB->ival));
  }
  //opA is an int, opB is a string
  else if (opA->type == 0 && opB->type == 2) {
    if (operator->sval[0] == '+')
      return newValueI((opA->ival + atoi(opB->sval)));
    else if (operator->sval[0] == '-')
      return newValueI((opA->ival - atoi(opB->sval)));
    else if (operator->sval[0] == '*')
      return newValueI((opA->ival * atoi(opB->sval)));
    else if (operator->sval[0] == '/')
      return newValueI((opA->ival / atoi(opB->sval)));
    else if (operator->sval[0] == '^')
      return newValueI((opA->ival ^ atoi(opB->sval)));
    else if (operator->sval[0] == '%')
      return newValueI((opA->ival % atoi(opB->sval)));
  }
  //opA is an double, opB is a string
  else if (opA->type == 1 && opB->type == 2) {
    if (operator->sval[0] == '+')
      return newValueR((opA->rval + atof(opB->sval)));
    else if (operator->sval[0] == '-')
      return newValueR((opA->rval - atof(opB->sval)));
    else if (operator->sval[0] == '*')
      return newValueR((opA->rval * atof(opB->sval)));
    else if (operator->sval[0] == '/')
      return newValueR((opA->rval / atof(opB->sval)));
    else if (operator->sval[0] == '^')
      return newValueR(pow(opA->rval,atof(opB->sval)));
    else if (operator->sval[0] == '%')
      return newValueR(fmod(opA->rval,atof(opB->sval)));
  }

  //string contatonation
  else if (opA->type == 2 && opB->type == 2) {
    if (operator->sval[0] == '+')
      return newValueS(concat(opA, opB));
  }
  return NULL;
}

char *concat(value *opA, value *opB) {
  char *a = opA->sval;
  char *b = opB->sval;
  char *c = malloc(sizeof(char) * (strlen(a) + strlen(b) + 1));
  if (c == 0)
    Fatal("out of memory\n");
  sprintf(c,"%s%s",a,b);
  return c;
}

Queue **convertToPost(Queue *q) {
  //Initialize Stack, postFix Queue, and temp VARIABLE
  Stack *s = createStack();
  Queue *postFix = createQueue();
  value *v;
  Queue **outPut = (Queue **)malloc(sizeof(Queue *) * lines);
  int i = 0; //placeholder for walking array of queues

  //While items exist in the queue, run this
  while (q->front != NULL) {
    //remove from the queue
    v = deQueue(q);
    if (v->type == 4) {
        //add to stack if open parentheses
        if (v->sval[0] == '(')
            push(s,v);
        //if closed paren, remove from stack until open paren found
        else if (v->sval[0] == ')') {
            while (s->rear->value->sval[0] != '(') {
              enQueue(postFix,pop(s));
            }
            pop(s); //discarding the open paren
        }
        //if OPERATOR, add to stack unless the following
        else {
          while (s->rear != NULL
                && s->rear->value->sval[0] != '('
                && priority(v) <= priority(s->rear->value)) {
            enQueue(postFix,pop(s));
            }
          push(s,v);
        }
    }
    //anything else is added to postFix Queue
    else if (v->type == 5) {
      //Clear out stack
      while (s->rear != NULL) {
        enQueue(postFix,pop(s));
      }
      outPut[i] = postFix;
      //move the postfix queue to the output
      postFix = createQueue();
      ++i;
    }
    else
        enQueue(postFix,v);
  }
  return outPut;
}

int priority(value *v) {
  if (v->sval[0] == '=')
    return (0);
  else if(v->sval[0] == '+')
    return(1);
  else if (v->sval[0] == '-')
    return(2);
  else if(v->sval[0] == '*')
    return(3);
  else if (v->sval[0] == '/')
    return(4);
  else if (v->sval[0] == '%')
      return(5);
  else if(v->sval[0] == '^')
    return(6);
  return(7);
}

Queue *readFile(FILE *fp) {
    Queue *q1 = createQueue();
    value *tempVal;
    while(!feof(fp)) {
        tempVal = readValue(fp);
        if (tempVal != NULL)
          enQueue(q1,tempVal);
      }
    return q1;
}

value *readValue(FILE *fp) {
  value *v;
  if (stringPending(fp))
    v = newValueS(readString(fp));
  else {
      char *token = readToken(fp);
      if (token == NULL)
        return NULL;
      if (strchr(token,'.') != 0){
        v = newValueR(atof(token));
      } // dot found!
      else if (((strlen(token) > 1) && *token == '-') || isdigit(*token) ) {
        v = newValueI(atoi(token));
      }
      else if (strcmp(token,"var") == 0)
        {
          v = newValueV(readToken(fp));
           insert(b,init(v));
        }
      else if (isalpha(*token))
          v = newValueV(token);
      else if (token[0] == ';') {
        ++lines;
        v = newValueE(token);
      }
      else
        v = newValueO(token);
  }
  return v;
}

void printQueue(Queue *q) {
  value *v;
  while (q->front != NULL) {
    v = deQueue(q);
    if (v->type == 0)
      printf("%d ", v->ival);
    else if (v->type == 1)
      printf("%f ", v->rval);
    else
      printf("%s ", v->sval);
  }
  printf("\n");
  return;
}

void Fatal(char *fmt, ...) {
  va_list ap;
  fprintf(stderr,"An error occured: ");
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  exit(-1);
}

void ProcessOptions(int argc, char **argv) {
  int argIndex = 1;

  while (argIndex < argc) {
    if (strcmp(argv[argIndex], "-v") == 0)
      name = 1;
    else if (strcmp(argv[argIndex], "-d") == 0)
      postfix = 1;
    else if (argv[argIndex][0] == '-') {
      printf("Option not understood");
      return;
    }
    else {
      fileRead = 1;
      file = argv[argIndex];
    }
    ++argIndex;
  }
  return;
}
