#define _CRT_SECURE_NO_WARNINGS // pro zruseni warningu visual studia
#include "headers\interpret.h"
#include "headers\testWriteOut.h"

void interpret(tInstrList iList,TsTree *ts) {
	debug("[INTERPRET] Staring interpret...\n");
	//stack pro vnitrni mezi vypocty a parametry fci
	Stack interStack = stackInit(100);

	tInstr ins; // aktualni instrukce

	// tabulka ramcu
	StackFrame *sf = newFrame(NULL,*ts,"Main.run",NULL,NULL);

	
	//printf("### END TEST SF wOut\n");

	//StackFrame *sf = ts; // POUZE PRO TEST

	Operand *dest = NULL, *src1 = NULL, *src2 = NULL;
	char *tmpStr1,*tmpStr2;
	Data tmpData;

	instrListSetActiveFirst(&iList);


	debug("[INTERPRET] Content of FRAME before first execute\n");
	testWriteOutFrame(sf);

	// prochazim seznam instrukci az do konce
	while (!instrListGetActiveInstr(&iList, &ins)) {	
		
		debug("[INTERPRET] Instruction execute: \n ");
		testWriteOutI(ins);

		dest = src1 = src2 = tmpStr1 = tmpStr2= NULL; // reset adres

//TODO pokud jsou dve NULL 


		int destT, src1T, src2T;
		// Priradim zdroje a cile
		if (ins.addr2 == NULL && ins.addr3 == NULL) { // dest NULL NULL
			dest = ins.addr1;
			src1 = dest;

			destT = getType(dest);
			src1T = destT;
		}
		else if (ins.addr3 == NULL) { // dest/src1 src2 NULL
			dest = ins.addr1;
			src1 = dest;
			src2 = ins.addr2;

			destT = getType(dest);
			src1T = destT;
			src2T = getType(src2);
		}
		else { // src1 src2 dest
			dest = ins.addr3;
			src1 = ins.addr1;
			src2 = ins.addr2;

			destT = getType(dest);
			src1T = getType(src1);
			src2T = getType(src2);
		}

		//if (ins.addr3 == NULL) {
		//	dest = ins.addr1;
		//	src1 = ins.addr1;
		//	src2 = ins.addr2;
		//}
		//else {
		//	dest = ins.addr3;
		//	src1 = ins.addr1;
		//	src2 = ins.addr2;
		//}

		////typy operandu
		//int destT, src1T, src2T;
		//if(dest->type == name)
		//	destT = findInFrame(dest->value.name, sf)->type; // cil
		//if (dest != src1) // pokud nebyla dvou operandova instrukce
		//	src1T = getType(src1); //typ src1
		//else src1T = destT; // pokud byla dvou src1 je kopie dest
		//if(src2)
		//src2T = getType(src2);

//ENDTODO

		//printf("switch");
		switch (ins.instr) {
//Zakladni operace
			//ADD
			break;
		case I_MOV:
			switch (destT) {
				case t_int:
					findInFrame(dest->value.name, sf)->value.v_int = byType(src2);
					break;
				case t_double:
					findInFrame(dest->value.name, sf)->value.v_double = byType(src2);
					break;
				case t_string:
				//TODO nema se udelat kopie retezce??
					findInFrame(dest->value.name, sf)->value.v_string = makeString((src2->type == name) ? findInFrame(src2->value.name, sf)->value.v_string : src2->value.v_string);
					break;
				default: break;
			}
			break;
		case I_CALL:
			//kam ulozit return? na stack? nebo si necham tady v promenne adresu a pri ret to tam poslu
			//vytvorim novy ramec
			//prepnu se do neho
			//nactu paramety
			//continue a pokracuju v instrukcich 

			sf = newFrame(sf, *ts, ins.addr1->value.name, ins.addr3, iList.active);
			instrListSetActive(&iList, tsFind(ts, ins.addr1->value.name)->addr);
			extractParams(sf, ts, interStack);
			continue;

			break;
		case I_RET:
			//vlozim do returnu
			// odstnim ramec
			//prepnu se z5
			//pokud jsem v NULL tak je konec Main.run
			if (ins.addr1 && sf->ret) {
				switch (destT) {
				case t_int:
					sf->ret->value.v_int = byType(src1);
					break;
				case t_double:
					sf->ret->value.v_double = byType(src1);
					break;
				case t_string:
					sf->ret->value.v_string = makeString((dest->type == name) ? findInFrame(dest->value.name, sf)->value.v_string : dest->value.v_string);
					break;
				default: break;
				}
			}
			
			instrListSetActive(&iList,sf->lastActive); // pokud je konec Main.run tak je to null a smycka konci
			sf = deleteFrame(sf); // navraceni otcovskeho ramce		

			break;
		case I_PUSH:
			switch (destT){
				case t_int: 
				case t_double: 
					tmpData = *findInFrame(dest->value.name, sf);
					stackPush(interStack,tmpData);
				case t_string: 
					tmpData = *findInFrame(dest->value.name, sf);
					tmpData.value.v_string = makeString(tmpData.value.v_string); // novou kopii 
					stackPush(interStack, tmpData); // vlozim na stack
					break;
				default:
				break;
			}
			break;
		case I_POP:
			switch (destT){
				case t_int:
				case t_double:
				case t_string: // retezec je vytvoren pres push, nemusim tvorit novy 
			//TODO mozna oprava u str free puvodni str
					stackPop(interStack,&tmpData);
					findInFrame(dest->value.name, sf)->value = tmpData.value; // NERUCIM za spravnost 
				default:
					break;
			}
			break;

//JMPs
		case I_JMP: break;
		case I_JMPE: break;
		case I_JMPNE: break;
		case I_JMPL: break;
		case I_JMPLE: break;
		case I_JMPG: break;
		case I_JMPGE: break;


//Matematicke operace
		case I_ADD:
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
					
					//konverze dat
					if (src1T == t_string) {
						tmpStr1 = (src1->type == name) ? findInFrame(src1->value.name, sf)->value.v_string : src1->value.v_string;
					}
					else if (src1T == t_int) {
						tmpStr1 = intToString((src1->type == name) ? findInFrame(src1->value.name, sf)->value.v_int : src1->value.v_int);
					}
					else {
						tmpStr1 = intToString((src1->type == name) ? findInFrame(src1->value.name, sf)->value.v_double : src1->value.v_double);
					}

					if (src2 == t_string) {
						tmpStr1 = (src1->type == name) ? findInFrame(src2->value.name, sf)->value.v_string : src2->value.v_string;
					}
					else if (src2T == t_int) {
						tmpStr1 = intToString((src2->type == name) ? findInFrame(src2->value.name, sf)->value.v_int : src2->value.v_int);
					}
					else {
						tmpStr1 = intToString((src2->type == name) ? findInFrame(src2->value.name, sf)->value.v_double : src2->value.v_double);
					}
					findInFrame(dest->value.name, sf)->value.v_string = cat(tmpStr1,tmpStr2);
					//printf("stringOP\n");
					break;
				default: break;
			}

			break;
		case I_SUB:
			switch (destT) {
				case t_int:
					if (dest != src1) {
						findInFrame(dest->value.name, sf)->value.v_int = byType(src1);
					}
					findInFrame(dest->value.name, sf)->value.v_int -= byType(src2);
					break;
				case t_double:
					if (dest != src1) {
						findInFrame(dest->value.name, sf)->value.v_double = byType(src1);
					}
					findInFrame(dest->value.name, sf)->value.v_double -= byType(src2);
					break;
				default: break;
			}
			break;
		case I_MUL:
			switch (destT) {
				case t_int:
					if (dest != src1) {
						findInFrame(dest->value.name, sf)->value.v_int = byType(src1);
					}
					findInFrame(dest->value.name, sf)->value.v_int *= byType(src2);
					break;
				case t_double:
					if (dest != src1) {
						findInFrame(dest->value.name, sf)->value.v_double = byType(src1);
					}
					findInFrame(dest->value.name, sf)->value.v_double *= byType(src2);
					break;
				default: break;
			}
			break;
		case I_DIV:
			switch (destT) {
				case t_int:
					if (dest != src1) {
						findInFrame(dest->value.name, sf)->value.v_int = byType(src1);
					}
					findInFrame(dest->value.name, sf)->value.v_int /= byType(src2);
					break;
				case t_double:
					if (dest != src1) {
						findInFrame(dest->value.name, sf)->value.v_double = byType(src1);
					}
					findInFrame(dest->value.name, sf)->value.v_double /= byType(src2);
					break;
				default: break;
			}
			break;

		case I_INC:
			switch (destT) {
				case t_int:
					findInFrame(dest->value.name, sf)->value.v_int++;
					break;
				case t_double:
					findInFrame(dest->value.name, sf)->value.v_double++;
					break;
				default: break;
			}
			break;
		case I_DEC:
			switch (destT) {
				case t_int:
					findInFrame(dest->value.name, sf)->value.v_int--;
					break;
				case t_double:
					findInFrame(dest->value.name, sf)->value.v_double--;
					break;
				default: break;
			}
			break;

//Vstup - vystup
		case I_READ:
			switch(destT) {
				case t_int: 
					//findInFrame(dest->value.name, sf)->value.v_int = readInt();
					break;
				case t_double: 
					//findInFrame(dest->value.name, sf)->value.v_double = readDouble();
					break;
				case t_string: 
					//findInFrame(dest->value.name, sf)->value.v_string = readString();
					break;
				default: break;
			}
			break;
		case I_WRITE:

			//TODO pretyp pak write
			switch (destT) {
				case c_int: 
					printf("%d", dest->value.v_int);
					break;
				case c_double: 
					printf("%g", dest->value.v_double);
					break;
				case c_string: 
					printf("%s", dest->value.v_string);
					break;
				case name: 
					printf("%s", varToString(findInFrame(dest->value.name,sf)));
					break;
			}


			break;
		default: break;
		}

		debug("[INTERPRET] Content of FRAME after execute\n");
		testWriteOutFrame(sf);

		instrListSetActiveNext(&iList); // posunu aktivitu na další 
	}//while ins
	debug("[INTERPRET] Ending inrepret...\n");
}

//TODO extrahuje parametry funkce
void extractParams(StackFrame *sf, TsTree ts, Stack stack) {
	int cpar = 0; // TODO pocet parametru
	Data tmp;

	for (int i = cpar; i >= 0; i--) {
		stackPop(stack, &tmp);
		sf->data[i].value = tmp.value;
	}
}