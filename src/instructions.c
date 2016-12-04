#include "headers\instructions.h"
#include <stdio.h>
#include <stdlib.h>

void instrListInit(tInstrList *list) {
	list->first = NULL;
	list->last = NULL;
	list->active = NULL;
}

void instrListFree(tInstrList *list) {
	tInstrListItem *tmp;
	while (list->first != NULL) {
		tmp = list->first;
		list->first = list->first->next;
		free(tmp);
	}
}

int instrListAddInstr(tInstrList *list, tInstr instr) {
	tInstrListItem *instrItem = malloc(sizeof(tInstrListItem));
	if (instrItem == NULL) return 1;

	instrItem->instr = instr;
	instrItem->next = NULL;

	if (list->first == NULL) //pokud je prvni
		list->first = instrItem;
	else
		list->last->next = instrItem;
	list->last = instrItem;

	return 0;
}

int instrListGetActiveInstr(tInstrList *list, tInstr *instr) {
	if (list->active == NULL) // neni aktivni prvek
		return 1;

	*instr = list->active->instr;
	return 0;
}

void instrListSetActive(tInstrList *list, tInstrListItem *active) {
	list->active = active;
}

void instrListSetActiveNext(tInstrList *list) {
	if(list->active) // pokud je kam posouvat
		list->active = list->active->next;
}

void instrListSetActiveFirst(tInstrList *list) {
	list->active = list->first;
}
