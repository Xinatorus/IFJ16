#include "headers\framework.h"
#include <stdio.h>
#include <stdlib.h>


//vraci index na promennou ve stackframe
Data *findInFrame(char *name, StackFrame *sf) {
	for (int i = 0; i < sf->size; i++)
		if (!strcmp(name, sf->data[i].name)) return &(sf->data[i]);

	return NULL;
}

//vklada novy ramec na VRCHOL
StackFrame *newFrame(StackFrame *parent, void *ts) {
	int size = 1; // dohledat v TS
	StackFrame *sf = malloc(sizeof(StackFrame));
	if (sf == NULL) return NULL;
	sf->data = malloc(sizeof(Data)*size);
	if (sf->data == NULL) {
		free(sf);
		return NULL;
	}
	sf->child = parent->child; // melo by byt VZDY null! 
	parent->child = sf;
	sf->parent = parent;
	//TODO vlozeni jmen podle TS parametry budou nejspise ve stacku tudis push/pop


}

//odstanuje posledni ramec ze zasobniku
void deleteFrame(StackFrame *sf) {
	sf->parent = sf->child;
	free(sf->data);
	free(sf);
}