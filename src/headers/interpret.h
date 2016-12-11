#ifndef INTERPRET_H
#define INTERPRET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructions.h"
#include "tstree.h"
#include "stack.h"
#include "framework.h"
#include "strings.h"
#include "ial.h"
#include "framework.h"
#include "io.h"
#include "tstree.h"
#include "valgrind.h"
#include "error.h"

typedef struct lAdress {
	char *name;
	tInstrListItem *addr;
	struct lAdress *next;
}labelAdress;

// zkraceni zapisu
#define valueByType(var,typ) ((var->type == name) ? findInFrame(var->value.name, sf)->value.typ : var->value.typ)
#define byType(var) (var##T == t_int) ? valueByType(var, v_int) : valueByType(var, v_double)
#define getType(var) (var->type == name) ? findInFrame(var->value.name, sf)->type : var->type
#define getIntVar(var) (var->type == name) ? findInFrame(var->value.name, sf)->value.v_int : var->value.v_int

void interpret(tInstrList instr,TsTree *root, labelAdress *la);
void extractParams(StackFrame *sf, TsTree root, Stack stack);
void clearAll(StackFrame *sf, TsTree *root, Stack interStack,tInstrList *iList);

//TODO obalit do makra
//dest->value.v_int += (src1->type == t_int) ? src1->value.v_int : src1->value.v_double;



labelAdress *labelAdressInit();
void addLabelAdress(labelAdress *la, char *name, tInstrListItem *addr);
tInstrListItem *getLabelAdress(labelAdress *la, char *name);
void deleteLabels(labelAdress la);

#endif // include guard
