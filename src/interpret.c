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

	Operand *dest = NULL, *src1 = NULL, *src2 = NULL;

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

			dest = src1 = src2 = NULL; // reset adres

			// Priradim zdroje a cile
			if (ins.addr3 == NULL) { 
				dest = ins.addr1;
				src1 = ins.addr1;
				src2 = ins.addr2;
			}
			else {
				dest = ins.addr3;
				src1 = ins.addr1;
				src2 = ins.addr2;
			}
			
			//typy    (dest->type == name) ? findInFrame(dest->value.name, sf)->type : dest->type;
			int destT, src1T, src2T;

			destT = findInFrame(dest->value.name, sf)->type; // cil
			if (dest != src1) // pokud nebyla dvou operandova instrukce
				src1T = getType(src1); //typ src1
			else src1T = destT; // pokud byla dvou src1 je kopie dest
			src2T = getType(src2);

			//printf("type2: %d\n", getType(src2));

			//typ destinace
			switch (destT) { 
				case t_int: // int + int/double only
					//printf("intOP\n");
					if(dest != src1){ // nepotrebuju delat kopii toho sameho
						findInFrame(dest->value.name, sf)->value.v_int = byType(src1);
					}
					//printf("%d+%d\n", findInFrame(dest->value.name, sf)->value.v_int, byType(src2));

					findInFrame(dest->value.name, sf)->value.v_int += byType(src2);

					//printf("%d+%d\n", findInFrame(dest->value.name, sf)->value.v_int, byType(src2));
					break;
				case t_double: 
					//printf("bouble\n");
					if (dest != src1) {
						findInFrame(dest->value.name, sf)->value.v_double = byType(src1);
					}
					findInFrame(dest->value.name, sf)->value.v_double += byType(src2);
					break;
				case t_string: // konkatenace retezcu str + str/int/double
					//zatim jen str+str bez konverze
					
					
					findInFrame(dest->value.name, sf)->value.v_string = cat(
						(src1->type == name) ? findInFrame(src1->value.name, sf)->value.v_string : src1->value.v_string,
						(src2->type == name) ? findInFrame(src2->value.name, sf)->value.v_string : src2->value.v_string
					);


					//printf("stringOP\n");
					break;
				default: break;
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

	sf->data[2].name = "B";
	sf->data[2].type = t_double;
	sf->data[2].value.v_double = 1;

	sf->data[1].name = "C";
	sf->data[1].type = t_string;
	sf->data[1].value.v_string = "hello";

	testWriteOutFrame(sf);

	tInstrList list;
	instrListInit(&list);

	instrListAddInstr(&list, (tInstr) { I_ADD, &(Operand){name,.value.name="C"}, &(Operand) { name, .value.name = "C" }, NULL });

	interpret(list,sf);

	testWriteOutFrame(sf);
	

}