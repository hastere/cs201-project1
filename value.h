
/*
**
Created by Andrew Stere for use in Calculon
**
*/
#ifndef VALUE_H
#define VALUE_H


typedef struct value
    {
    int type;
    int ival;
    double rval;
    char *sval;
    } value;

extern int INTEGER;
extern int REAL;
extern int STRING;
extern int VARIABLE;
extern int OPERATOR;

extern value *newValueI(int);
extern value *newValueR(double);
extern value *newValueS(char *);
extern value *newValueV(char *);
extern value *newValueO(char *);
extern value *newValueE(char *);

#endif
