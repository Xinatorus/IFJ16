#ifndef INSTRUCTIONS
#define INSTRUCTIONS

//TODO Pridat instrukcni sadu
typedef enum {
	//em..
	I_JMP,
	I_MOV,
	I_CALL,
	I_RET,
	I_CMP,

	//binary
	I_AND,
	I_OR,
	I_XOR,
	I_NOT,

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

#endif // !INSTRUCTIONS
