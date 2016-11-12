/* ========================================================================== */
/* Jmena:   .......                                                           */
/* Soubor:  error.c                                                           */
/* Faze:    Chybove stavy                                                     */
/* Datum:   24.10.2016                                                        */
/* ========================================================================== */

#include <stdio.h>
#include "errors.h"


int vypisChybu(int chyba)
{
	switch(chyba)
	{
		case USPES_PREKL:
			break;
		case LEXIK_ERROR:
			fprintf(stderr," - Chyba v programe v ramci lexikalnej analyzy (chybna struktura aktualneho lexemu).\n");
			break;
		case SYNTA_ERROR:
			fprintf(stderr," - Chyba v programe v ramci syntaktickej analyzy (chybna syntax struktury programu).\n");
			break;
		case SEMAN_UNDE:
			fprintf(stderr," - Semanticka chyba - nedefinovana funkcia/premenna, pokus o redefinovanie funkcie/premennej. \n");
			break;
		case SEMAN_TYPE:
			fprintf(stderr," - Semanticka chyba typovej kompatibility v aritmeticktych, retazcovych a relacnych vyrazoch, pripadne nespravny pocet ci typ parametrov pri volani funkcie.\n");
			break;
		case SEMAN_OTHER:
			fprintf(stderr," - Ostatne semanticke chyby.\n");
			break;
		case BEH_ERROR_NUM:
			fprintf(stderr," - Behova chyba pri nacitani ciselnej hodnoty zo vstupu.\n");
			break;
		case BEH_ERROR_NEINI:
			fprintf(stderr," - Behova chyba pri praci s neinicializovanou premennou.\n");
			break;
		case BEH_ERROR_DEL_NUL:
			fprintf(stderr," - Behova chyba delenie nulou.\n");
			break;
		case BEH_ERROR_OST:
			fprintf(stderr," - Ostatne behove chyby.\n");
			break;
		case INTER_ERROR:
			fprintf(stderr," - Interna chyba interpretu tj. neovplyvnitelna vstupnym programom (napr. chyba alokacie pamati, chyba pri otvarani suboru s riadiacim programom, nespravne parametre prikazoveho riadku).\n");
			break;
	}
	return chyba;
}
