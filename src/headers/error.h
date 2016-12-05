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
	USPES_PREKL = 0,			/* �iadna chyba. */
	LEXIK_ERROR = 1,			/* 1 - Chyba v programe v r�mci lexik�lnej anal�zy (chybn� �trukt�ra aktu�lneho lex�mu). */
 	SYNTA_ERROR = 2,			/* 2 - Chyba v programe v r�mci syntaktickej anal�zy (chybn� syntax �trukt�ry programu). */
 	SEMAN_UNDE = 3,	            /* 3 - S�mantick� chyba - nedefinovan� funkcia/premenn�, pokus o redefinovanie funkcie/premennej. */
 	SEMAN_TYPE = 4,	            /* 4 - S�mantick� chyba typovej kompatibility v aritmetick�ch, re�azcov�ch a rela�n�ch v�razoch,
                                    pr�padne nespr�vny po�et �i typ parametrov pri volan� funkcie. */
 	SEMAN_OTHER = 6,		    /* 6 - Ostatn� s�mantick� chyby. */
 	BEH_ERROR_NUM = 7,			/* 7 - Behov� chyba pri na��tan� ��selnej hodnoty zo vstupu. */
 	BEH_ERROR_NEINI = 8,		/* 8 - Behov� chyba pri pr�ci s neinicializovanou premennou. */
 	BEH_ERROR_DEL_NUL = 9,		/* 9 - Behov� chyba delenie nulou. */
 	BEH_ERROR_OST = 10,			/* 10 - Ostatn� behov� chyby. */
 	INTER_ERROR = 99	        /* 99 - Intern� chyba interpretu tj. neovplyvnite�n� vstupn�m programom (napr. chyba alok�cie
                                    pam�ti, chyba pri otv�ran� s�boru s riadiacim programom, nespr�vne parametre pr�kazov�ho
                                    riadku at�.). */
};

// Funkce pro zpusobeni chyby, zastavi beh programu (pokud to neni USPES_PREKL)
void error(int chyba);

#endif // include guard
