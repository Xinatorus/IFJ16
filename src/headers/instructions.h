#ifndef INSTRUCTIONS
#define INSTRUCTIONS

// Instrunkci sada
typedef enum {
	//em..
	I_JMP,
	I_MOV,
	I_CALL,
	I_RET,
	I_PUSH,
	I_POP,

	//logic
	I_EQ,
	I_NEQ,
	I_LES,
	I_LESE,
	I_GRE,
	I_GREE,


	//math
	I_ADD,
	I_SUB,
	I_MUL,
	I_DIV,

	I_INC,
	I_DEC,

	//strings
	I_READ,
	I_WRITE,

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


#endif // !INSTRUCTIONS