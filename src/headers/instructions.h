#ifndef INSTRUCTIONS
#define INSTRUCTIONS

//TODO Pridat instrukcni sadu
#define JMP 
#define CALL 


typedef struct {
	int type;
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

tInstr instrListGetActiveInstr(tInstrList *list, tInstr instr);
void instrListSetActive(tInstrList *list, tInstrListItem *active);
void instrListSetActiveFirst(tInstrList *list);
void instrListSetActiveNext(tInstrList *list);

#endif // !INSTRUCTIONS
