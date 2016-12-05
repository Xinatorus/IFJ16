#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H


#include <stdio.h>
#include <stdlib.h>

#define FOREACH_INSTR(INS) \
        INS(I_JMP) \
		INS(I_MOV) \
		INS(I_CALL) \
		INS(I_RET) \
		INS(I_PUSH) \
		INS(I_POP) \
		INS(I_EQ) \
		INS(I_NEQ) \
		INS(I_LES) \
		INS(I_LESE) \
		INS(I_GRE) \
		INS(I_GREE) \
		INS(I_ADD) \
		INS(I_SUB) \
		INS(I_MUL) \
		INS(I_DIV) \
		INS(I_INC) \
		INS(I_DEC) \
		INS(I_READ) \
		INS(I_WRITE) \

#define GENERATE_ENUM_INSTR(ENUM) ENUM,
#define GENERATE_STRING_INSTR(STRING) #STRING,


// Instrunkci sada
typedef enum {
	FOREACH_INSTR(GENERATE_ENUM_INSTR)
}Instructions;

typedef struct {
	enum {
		c_int,
		c_double,
		c_string,
		name
	}type;
	union {
		int v_int;
		double v_double;
		char *v_string;
		char *name;
	}value;
}Operand;


typedef struct {
	Instructions instr;
	Operand *addr1;
	Operand *addr2;
	Operand *addr3;
}tInstr;

typedef struct instrListItem {
	tInstr instr;
	struct instrListItem *next;
} tInstrListItem;

typedef struct {
	tInstrListItem *first;
	tInstrListItem *last;
	tInstrListItem *active;
} tInstrList;

void instrListInit(tInstrList *list);
void instrListFree(tInstrList *list);

int instrListAddInstr(tInstrList *list, tInstr instr);

int instrListGetActiveInstr(tInstrList *list, tInstr *instr);
void instrListSetActive(tInstrList *list, tInstrListItem *active);
void instrListSetActiveFirst(tInstrList *list);
void instrListSetActiveNext(tInstrList *list);

//TODO pridat makra pro tvorbu operandu/instrukce


#endif // include guard
