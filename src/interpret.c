#include "headers\interpret.h"
#include "headers\stack.h"
#include "headers\instructions.h"
#include "headers\strings.h"
#include "headers\ial.h"

void interpret(tInstrList iList) {
	//stack pro vnitrni mezi vypocty
	Stack interStack = stackInit(100);

	tInstr activeInstr; // aktualni instrukce

	// tabulka ramcu? resp. stack? ramcu?


	instrListSetActiveFirst(&iList);

	// prochazim seznam instrukci az do konce
	while (!instrListGetActiveInstr(&iList, &activeInstr)) {
		instrListSetActiveNext(&iList); // posunu aktivitu

		switch (activeInstr.instr) {
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
				//ADD
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
		}
	}

}