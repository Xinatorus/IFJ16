#ifndef STRINGS_H
#define STRINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valgrind.h"
#include "stack.h"

// prace s retezci

char *makeString(char *str);
char *cat(char *s1, char *s2);
char *varToString(Data *var);
char *intToString(int x);
char *doubleToString(double x);
char *getSubString(char *str, int index, int size);
int length(char* s);
int compare(char *s1, char *s2);


#endif // include guard
