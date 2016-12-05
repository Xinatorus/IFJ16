#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

/*
#include "ial.h"
#include "instructions.h"
#include "lex_anal.h"
#include "error.h"
#include "framework.h"
#include "interpret.h"
*/

//input-output

bool readInt();
double readDouble();
char *readString();

#endif // !IO
