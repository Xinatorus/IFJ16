#include "headers\testWriteOut.h"
#include "headers\interpret.h"
#include "headers\instructions.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC 1
#include <Crtdbg.h>
#define malloc(size) _malloc_dbg(size,_CLIENT_BLOCK,__FILE__,__LINE__)
#define free(addr) _free_dbg(addr,_CLIENT_BLOCK)
#endif

void hashWriteOut(HashTable hashTable) {
	printf("+----------------------------\n");
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++) {
		//sloupec
		if (hashTable[i].key != NULL) {
			printf("[%3d]: %s", i, hashTable[i].key);
			if (hashTable[i].next != NULL) {
				for (HashTable item = hashTable[i].next; item != NULL; item = item->next) {
					printf(", %s", item->key);
				}
			}
			printf("\n");
		}
	}
	printf("+----------------------------\n");
}

void hashTest() {/*
				 printf("Create HashTable...\n");
				 HashTable table = createHashTable(HASH_TABLE_SIZE);
				 if (table == NULL) {
				 printf("Create Error");
				 error(INTER_ERROR);
				 }
				 printf("Hash adr: %p\n", table);
				 writeOut(table);


				 printf("Add \"A\" to table...\n");
				 addToHashTable(table, "A", "0", 0);
				 writeOut(table);

				 printf("Add \"ANO\" to table...\n");
				 addToHashTable(table, "ANO", "0", 1);
				 writeOut(table);

				 printf("Add \"NE\" to table...\n");
				 addToHashTable(table, "NE", "0", 1);
				 writeOut(table);

				 printf("Search for ANO\n");
				 printf("adr: %p key: %s\n", searchInHashTable(table, "ANO"), searchInHashTable(table, "ANO")->key);
				 writeOut(table);

				 printf("Search for B\n");
				 if (searchInHashTable(table, "B") == NULL) printf("not found\n");
				 else
				 printf("adr: %p key: %s\n", searchInHashTable(table, "B"), searchInHashTable(table, "B")->key);
				 writeOut(table);

				 printf("Deleting table\n");
				 deleteHashTable(table);*/
}

//testovaci vypis struktury TS
void tsWriteOutTree(TsTree root) {
	if (root == NULL) {
		printf("Tree is empty\n");
		return;
	}

	printf("---------TREE---------\n");
	for (TsTree x = root; x != NULL; x = x->next) {
		printf("%c %s\n",195, x->name);
		for (TsTree t = x->child; t != NULL; t = t->next)
			printf("%c %c%c %s\n",179,192,196, t->name);
	}
	printf("----------------------\n");
}

void tsWriteOutTreeTS(TsTree root) {

}

void tsTest() {
	printf("TsTree Test...\n");
	TsTree root;
	tsTreeInit(&root);

	printf("Add Main\n");
	tsAdd(&root, "Main",0,NULL, NULL);
	tsWriteOutTree(root);

	printf("Add Bain\n");
	tsAdd(&root, "Bain", 0, NULL, NULL);
	tsWriteOutTree(root);

	printf("Add Main.run\n");
	tsAdd(&root, "Main.run", 0, NULL, NULL);
	tsWriteOutTree(root);

	printf("Add Main.main\n");
	tsAdd(&root, "Main.main", 0, NULL, NULL);
	tsWriteOutTree(root);

	printf("Add Dain\n");
	tsAdd(&root, "Dain", 0, NULL, NULL);
	tsWriteOutTree(root);

	printf("Add Bain.foo\n");
	tsAdd(&root, "Bain.foo", 0, NULL, NULL);
	tsWriteOutTree(root);

	printf("Deleting tree..\n");
	tsDel(&root);
	printf("tree deleted\n");
	tsWriteOutTree(root);

	printf("TsTree Test END...\n");
}


void testInsterpret() {
	//vytvorim nekolik instrukci ADD
	//vytvorim pravidlo ramec
	//interpretuju
	//vypisu ramec
	/*
	StackFrame *sf = malloc(sizeof(StackFrame));
	sf->child = NULL;
	sf->parent = NULL;
	sf->size = 3;
	sf->data = malloc(sizeof(Data) * 3);
	sf->data[0].name = "A";
	sf->data[0].type = t_int;
	sf->data[0].value.v_int = 5;

	sf->data[2].name = "B";
	sf->data[2].type = t_double;
	sf->data[2].value.v_double = 1;

	sf->data[1].name = "C";
	sf->data[1].type = t_string;
	sf->data[1].value.v_string = "hello";

	testWriteOutFrame(sf);

	tInstrList list;
	instrListInit(&list);

	instrListAddInstr(&list, (tInstr) { I_ADD, &(Operand){name, .value.name = "C"}, &(Operand) { name, .value.name = "C" }, NULL });

	interpret(list, sf);

	testWriteOutFrame(sf);

	*/
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
			printf("+%28s +%11s +%37s +\n", sf->data[i].name, "string", sf->data[i].value.v_string);
			break;
		default: printf("ERROR TYPE");
			break;
		}
	}

	printf("\n");

}

void testWriteOutInstr(tInstrList list) {
	static const char *INSTR_STRING[] = {
		//FOREACH_INSTR(GENERATE_STRING_INSTR)
	};

	printf("WriteOut Instruction list");
	for (tInstrListItem *tmp = list.first; tmp != NULL; tmp = tmp->next) {
		printf("%s ",INSTR_STRING[tmp->instr.instr]);
		if (tmp->instr.addr1 != NULL) {
			switch(tmp->instr.addr1->type) {
				case c_int: 
					printf("%d ", tmp->instr.addr1->value.v_int);
					break;
				case c_double: 
					printf("%g ", tmp->instr.addr1->value.v_double);
					break;
				case c_string: 
					printf("%s ", tmp->instr.addr1->value.v_string);
					break;
				case name: 
					printf("%s ",tmp->instr.addr1->value.name);
					break;
				default: break;
			}
		}
		else printf("NULL ");

		if (tmp->instr.addr2 != NULL) {
			switch (tmp->instr.addr1->type) {
			case c_int:
				printf("%d ", tmp->instr.addr2->value.v_int);
				break;
			case c_double:
				printf("%g ", tmp->instr.addr2->value.v_double);
				break;
			case c_string:
				printf("%s ", tmp->instr.addr2->value.v_string);
				break;
			case name:
				printf("%s ", tmp->instr.addr2->value.name);
				break;
			default: break;
			}
		}
		else printf("NULL ");

		if (tmp->instr.addr3 != NULL) {
			switch (tmp->instr.addr3->type) {
			case c_int:
				printf("%d ", tmp->instr.addr3->value.v_int);
				break;
			case c_double:
				printf("%g ", tmp->instr.addr3->value.v_double);
				break;
			case c_string:
				printf("%s ", tmp->instr.addr3->value.v_string);
				break;
			case name:
				printf("%s ", tmp->instr.addr3->value.name);
				break;
			default: break;
			}
		}
		else printf("NULL ");
		printf("\n");
	}
	printf("End of Instr\n");
}