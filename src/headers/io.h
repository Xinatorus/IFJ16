/* ------------------------------HLAVICKOVE SOUBORY----------------------------------- */
#include "headers\io.h"
#include "headers\ial.h"
#include "headers\instructions.h"
#include "headers\lex_anal.h"
#include "headers\error.h"
#include "headers\framework.h"
#include "headers\interpret.h"
/* ----------------------------------------------------------------------------------- */

#define STR_MAX 100000

char *readString();
bool readInt();
double readDouble();
int length(char* s);
int compare(char *s1, char *s2);
