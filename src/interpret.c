#include "headers\interpret.h"
#include "headers\stack.h"
#include "headers\instructions.h"
#include "headers\strings.h"
#include "headers\ial.h"
#include "headers\framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void interpret(tInstrList iList) {
	//stack pro vnitrni mezi vypocty
	Stack interStack = stackInit(100);

	tInstr ins; // aktualni instrukce

				// tabulka ramcu
	StackFrame *sf = newFrame(NULL, NULL);

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
				case t_string: break;
				default: break;
				}
			}
			else {

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