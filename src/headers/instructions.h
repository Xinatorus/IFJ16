#ifndef INSTRUCTIONS
#define INSTRUCTIONS

//TODO Pridat instrukcni sadu
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
	Instructions instr;
	void *addr1;
	void *addr2;
	void *addr3;
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

#define generateInstr(i,a1,a2,a3) tInstr instr = {i,a1,a2,a3}

#endif // !INSTRUCTIONS
