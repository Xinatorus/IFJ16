#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

/* ========================================================================== */
/* Jmena:   .......                                                           */
/* Soubor:  error.c                                                           */
/* Faze:    Chybove stavy                                                     */
/* Datum:   24.10.2016                                                        */
/* ========================================================================== */
enum chyboveStavy
{
	USPES_PREKL = 0,			/* iadna chyba. */
	LEXIK_ERROR = 1,			/* 1 - Chyba v programe v rámci lexikálnej analızy (chybná štruktúra aktuálneho lexému). */
 	SYNTA_ERROR = 2,			/* 2 - Chyba v programe v rámci syntaktickej analızy (chybná syntax štruktúry programu). */
 	SEMAN_UNDE = 3,	            /* 3 - Sémantická chyba - nedefinovaná funkcia/premenná, pokus o redefinovanie funkcie/premennej. */
 	SEMAN_TYPE = 4,	            /* 4 - Sémantická chyba typovej kompatibility v aritmetickıch, reazcovıch a relaènıch vırazoch,
                                    prípadne nesprávny poèet èi typ parametrov pri volaní funkcie. */
 	SEMAN_OTHER = 6,		    /* 6 - Ostatné sémantické chyby. */
 	BEH_ERROR_NUM = 7,			/* 7 - Behová chyba pri naèítaní èíselnej hodnoty zo vstupu. */
 	BEH_ERROR_NEINI = 8,		/* 8 - Behová chyba pri práci s neinicializovanou premennou. */
 	BEH_ERROR_DEL_NUL = 9,		/* 9 - Behová chyba delenie nulou. */
 	BEH_ERROR_OST = 10,			/* 10 - Ostatné behové chyby. */
 	INTER_ERROR = 99	        /* 99 - Interná chyba interpretu tj. neovplyvnite¾ná vstupnım programom (napr. chyba alokácie
                                    pamäti, chyba pri otváraní súboru s riadiacim programom, nesprávne parametre príkazového
                                    riadku atï.). */
};

// Funkce pro zpusobeni chyby, zastavi beh programu (pokud to neni USPES_PREKL)
void error(int chyba);

#endif // include guard
