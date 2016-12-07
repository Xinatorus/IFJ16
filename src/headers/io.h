#ifndef IO_H
#define IO_H

/* ------------------------------HLAVICKOVE SOUBORY----------------------------------- */
#include "headers\ial.h"
#include "headers\instructions.h"
#include "headers\lex_anal.h"
#include "headers\error.h"
#include "headers\framework.h"
#include "headers\interpret.h"
/* ----------------------------------------------------------------------------------- */

#define STR_MAX 100000

char *readString();
bool readInt(int *out);
double readDouble(double *out);


#endif // include guard
