#ifndef  TESTWRITEOUT_H
#define TESTWRITEOUT_H

#include "valgrind.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ial.h"
#include "instructions.h"
#include "lex_anal.h"
#include "synt_anal.h"
#include "error.h"
#include "framework.h"
#include "strings.h"
#include "tstree.h"



//ial
void hashWriteOut(HashTable hashTable);
void hashTest();

//tstree
void tsWriteOutTree(TsTree root);
void tsWriteOutTreeTS(TsTree root);
void tsTest();

#endif // ! TESTWRITEOUT_H

