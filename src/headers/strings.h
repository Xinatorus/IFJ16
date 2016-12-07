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


#endif // include guard
