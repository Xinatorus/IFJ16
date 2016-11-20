#include "headers\framework.h"
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

//testovaci vypis obsahu struktury
void testWriteOutFrame(StackFrame *sf) {
	printf("+FRAME: %d (%d %d)\n", sf, sf->parent, sf->parent);
	printf("+------------------------------------------------------------------------------+\n"); 
	printf("+                          ID +       TYPE +                                VALUE +\n");

	for (int i = 0; i < sf->size; i++) {
		switch (sf->data[i].type) {
		case t_int: 
			printf("+%28s +%11s +%37d +\n", sf->data[i].name, "int", sf->data[i].value.v_int);
			break;
		case t_double: 
			printf("+%28s +%11s +%37lf +\n", sf->data[i].name, "double", sf->data[i].value.v_double);
			break;
		case t_string: 
			printf("+%28s +%11s +%37s +\n",sf->data[i].name,"string", sf->data[i].value.v_string);
			break;
		default: printf("ERROR TYPE");
			break;
		}
	}

	printf("\n");
		
}