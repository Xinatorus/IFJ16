#include "headers\interpret.h"
#include "headers\stack.h"
#include "headers\instructions.h"
#include "headers\strings.h"
#include "headers\ial.h"
#include "headers\framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void interpret(tInstrList iList,void *ts) {
	//stack pro vnitrni mezi vypocty
	Stack interStack = stackInit(100);

	tInstr ins; // aktualni instrukce

	// tabulka ramcu
	//StackFrame *sf = newFrame(NULL, ts);
	StackFrame *sf = ts; // POUZE PRO TEST

	Data *dest, *src1, *src2;

	instrListSetActiveFirst(&iList);

	// prochazim seznam instrukci az do konce
	while (!instrListGetActiveInstr(&iList, &ins)) {
			
		instrListSetActiveNext(&iList); // posunu aktivitu

		switch (ins.instr) {
			//Zakladni operace
		case I_JMP:
			//ADD
			break;
		case I_MOV:
			//ADD
			break;
		case I_CALL:
			//ADD
			break;
		case I_RET:
			//ADD
			break;
		case I_PUSH:
			//ADD
			break;
		case I_POP:
			//ADD
			break;

			//Logicke operace
		case I_EQ:
			//ADD
			break;
		case I_NEQ:
			//ADD
			break;
		case I_LES:
			//ADD
			break;
		case I_LESE:
			//ADD
			break;
		case I_GRE:
			//ADD
			break;
		case I_GREE:
			//ADD
			break;


			//Matematicke operace
		case I_ADD:
			if (ins.addr3 == NULL) { // dest?
				Data *dest = findInFrame(ins.addr1->value.name, sf); // dest je addr1
				Data *src1;
				void *src; // odkaz na zdroj 

				switch (ins.addr2->type) { // typ 2. operandu
										   // jmeno takze musim najit koho 
				case name: src1 = findInFrame(ins.addr1->value.name, sf);
					switch (src1->type) { //podle typu zdroje priradim adresu
					case t_int: src = &(src1->value.v_int);
						break;
					case t_double: src = &(src1->value.v_double);
						break;
					case t_string: src = src1->value.v_string;
						break;
					}
					break;
					// konstanta
				case c_int:  src = &ins.addr2->value.c_int;
					break;
				case c_double: src = &ins.addr2->value.c_double;
					break;
				case c_string: src = ins.addr2->value.c_string;
					break;
				default: break;
				}


				switch (dest->type) {
				case t_int: dest->value.v_int += *(int*)src;
					break;
				case t_double: dest->value.v_double += *(double*)src;
					break;
				case t_string: 
					strcat(dest->value.v_string, src);
					break;
				default: break;
				}
			}
			else {
				//to same ale dest je addr3
			}
			break;
		case I_SUB:
			//ADD
			break;
		case I_MUL:
			//ADD
			break;
		case I_DIV:
			//ADD
			break;

		case I_INC:
			//ADD
			break;
		case I_DEC:
			//ADD
			break;

			//Prace s retezci
		case I_READ:
			//ADD
			break;
		case I_WRITE:
			//ADD
			break;
		default: break;
		}
	}

}


void testInsterpret() {
	//vytvorim nekolik instrukci ADD
	//vytvorim pravidlo ramec
	//interpretuju
	//vypisu ramec

	StackFrame *sf = malloc(sizeof(StackFrame));
	sf->child = NULL;
	sf->parent = NULL;
	sf->size = 3;
	sf->data = malloc(sizeof(Data) * 3);
	sf->data[0].name = "A";
	sf->data[0].type = t_int;
	sf->data[0].value.v_int = 5;

	sf->data[2].name = "C";
	sf->data[2].type = t_int;
	sf->data[2].value.v_int = 5;

	sf->data[1].name = "B";
	sf->data[1].type = t_string;
	sf->data[1].value.v_string = "Nejaky retezec";

	testWriteOutFrame(sf);

	tInstrList list;
	instrListInit(&list);

	instrListAddInstr(&list, (tInstr) { I_ADD, &(Operand){name,.value.name="A"}, &(Operand) { name, .value.name = "C" }, NULL });

	interpret(list,sf);

	testWriteOutFrame(sf);
	

}