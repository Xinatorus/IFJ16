#ifndef INTERPRET_H
#define INTERPRET_H

#include "instructions.h"
#include "tstree.h"
#include "stack.h"
#include "framework.h"

// zkraceni zapisu
#define valueByType(var,typ) ((var->type == name) ? findInFrame(var->value.name, sf)->value.typ : var->value.typ)
#define byType(var) (var##T == t_int) ? valueByType(var, v_int) : valueByType(var, v_double)
#define getType(var) (var->type == name) ? findInFrame(var->value.name, sf)->type : var->type


void interpret(tInstrList instr,TsTree *root);
void extractParams(StackFrame *sf, TsTree ts, Stack stack);

//TODO obalit do makra
//dest->value.v_int += (src1->type == t_int) ? src1->value.v_int : src1->value.v_double;


#endif // include guard
