/*
*	Projekt:	IFJ16
*	Vedouci:	xztef02
*	Autori:		xsztef02 xsipos03 xszucs01 xstolj00
*				Patrik Sztefek, Marek Sipos, Tomas Szucz, Jakub Stol
*/
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
	ERR_OK = 0,			/* �iadna chyba. */
	ERR_LEX = 1,			/* 1 - Chyba v programe v r�mci lexik�lnej anal�zy (chybn� �trukt�ra aktu�lneho lex�mu). */
 	ERR_SYNT = 2,			/* 2 - Chyba v programe v r�mci syntaktickej anal�zy (chybn� syntax �trukt�ry programu). */
 	ERR_SEM_DEF = 3,	            /* 3 - S�mantick� chyba - nedefinovan� funkcia/premenn�, pokus o redefinovanie funkcie/premennej. */
 	ERR_SEM_TYPE = 4,	            /* 4 - S�mantick� chyba typovej kompatibility v aritmetick�ch, re�azcov�ch a rela�n�ch v�razoch,
                                    pr�padne nespr�vny po�et �i typ parametrov pri volan� funkcie. */
 	ERR_SEM_OTHER = 6,		    /* 6 - Ostatn� s�mantick� chyby. */
 	ERR_RUN_NUM = 7,			/* 7 - Behov� chyba pri na��tan� ��selnej hodnoty zo vstupu. */
 	ERR_RUN_INIT = 8,		/* 8 - Behov� chyba pri pr�ci s neinicializovanou premennou. */
 	ERR_RUN_DEV = 9,		/* 9 - Behov� chyba delenie nulou. */
 	ERR_RUN_OTHER = 10,			/* 10 - Ostatn� behov� chyby. */
 	ERR_INTER = 99	        /* 99 - Intern� chyba interpretu tj. neovplyvnite�n� vstupn�m programom (napr. chyba alok�cie
                                    pam�ti, chyba pri otv�ran� s�boru s riadiacim programom, nespr�vne parametre pr�kazov�ho
                                    riadku at�.). */
};

// Funkce pro zpusobeni chyby, zastavi beh programu (pokud to neni USPES_PREKL)
void error(int chyba);

#endif // include guard
