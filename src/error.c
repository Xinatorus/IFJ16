/* ========================================================================== */
/* Jmena:   .......                                                           */
/* Soubor:  error.c                                                           */
/* Faze:    Chybove stavy                                                     */
/* Datum:   24.10.2016                                                        */
/* ========================================================================== */

#define _CRT_SECURE_NO_WARNINGS // pro zruseni warningu visual studia
#include "headers/error.h"


void error(int chyba)
{
	switch(chyba)
	{
		case ERR_OK:
			break;
		case ERR_LEX:
			fprintf(stderr," - Chyba v programe v ramci lexikalnej analyzy (chybna struktura aktualneho lexemu).\n");
			break;
		case ERR_SYNT:
			fprintf(stderr," - Chyba v programe v ramci syntaktickej analyzy (chybna syntax struktury programu).\n");
			break;
		case ERR_SEM_DEF:
			fprintf(stderr," - Semanticka chyba - nedefinovana funkcia/premenna, pokus o redefinovanie funkcie/premennej. \n");
			break;
		case ERR_SEM_TYPE:
			fprintf(stderr," - Semanticka chyba typovej kompatibility v aritmeticktych, retazcovych a relacnych vyrazoch, pripadne nespravny pocet ci typ parametrov pri volani funkcie.\n");
			break;
		case ERR_SEM_OTHER:
			fprintf(stderr," - Ostatne semanticke chyby.\n");
			break;
		case ERR_RUN_NUM:
			fprintf(stderr," - Behova chyba pri nacitani ciselnej hodnoty zo vstupu.\n");
			break;
		case ERR_RUN_INIT:
			fprintf(stderr," - Behova chyba pri praci s neinicializovanou premennou.\n");
			break;
		case ERR_RUN_DEV:
			fprintf(stderr," - Behova chyba delenie nulou.\n");
			break;
		case ERR_RUN_OTHER:
			fprintf(stderr," - Ostatne behove chyby.\n");
			break;
		case ERR_INTER:
			fprintf(stderr," - Interna chyba interpretu tj. neovplyvnitelna vstupnym programom (napr. chyba alokacie pamati, chyba pri otvarani suboru s riadiacim programom, nespravne parametre prikazoveho riadku).\n");
			break;
	}
	if (chyba != ERR_OK)
		exit(chyba);
}
