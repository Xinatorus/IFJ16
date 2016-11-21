#ifndef STRINGS_H
#define STRINGS_H

// prace s retezci
#include "headers\stack.h"

char *makeString(char *str);
char *cat(char *s1, char *s2);
char *varToString(Data var);
char *intToString(int x);
char *doubleToString(double x);

#endif // include guard
