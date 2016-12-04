#include "headers\framework.h"
#include "headers\strings.h"
#include <stdio.h>
#include <stdlib.h>


//vraci odkaz na promenou
Data *findInFrame(char *name, StackFrame *sf) {
	for (int i = 0; i < sf->size; i++) {
		//printf("compare: %s - %s, %d\n", name, sf->data[i].name, strcmp(name, sf->data[i].name));
		if (!strcmp(name, sf->data[i].name)) { 
			//printf("have match \n");
			return &(sf->data[i]); }
		//printf("not same\n");
	}
		

	return NULL;
}

//vklada novy ramec na VRCHOL,
StackFrame *newFrame(StackFrame *parent, TsTree root, char *name) {

	TsTree ts = tsFind(root, name);

	int size = ts->varCount; // pocet promennych, dohledat v TS
	StackFrame *sf = malloc(sizeof(StackFrame));
	if (sf == NULL) return NULL;
	sf->data = malloc(sizeof(Data)*size);
	if (sf->data == NULL) {
		free(sf);
		return NULL;
	}

	sf->identifier = makeString(name);
	if (parent) { //pokud neni prvni
		sf->child = parent->child; // melo by byt VZDY null! 
		parent->child = sf;
	}
	sf->parent = parent;
	//TODO vlozeni jmen podle TS
	
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++) {
		//sloupec
		for (HashTable item = ts->ts[i].next; item != NULL; item = item->next) {
			if (item->type[0] == 'V') { // pokud je pormenna
				sf->data[item->index].name = makeString(item->key);// jmeno promenne

				switch (item->type[1]) { //datovy typ
				case 'I': 
					sf->data[item->index].type = t_int;
					break;
				case 'D': 
					sf->data[item->index].type = t_double;
					break;
				case 'S': 
					sf->data[item->index].type = t_string;
					break;
				default: break;
				}
			}
		}
	}

	return sf;
}

//odstanuje posledni ramec ze zasobniku
void deleteFrame(StackFrame *sf) {
	sf->parent->child = sf->child; // TODO nejsem si jisty ? melo by to byt propojeni seznamu
	free(sf->data);
	free(sf);
}

