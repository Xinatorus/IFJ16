#ifndef SYNT_ANAL_H
#define SYNT_ANAL_H

#include "lex_anal.h"


/* List of possible non-terminals */
typedef enum {
    NT_PROGRAM,
    NT_TRIDA,
    NT_SEZNAM_DEFINIC_STATIC,
    NT_DEFINICE_STATIC,
    NT_DEFINICE_PROMENNA,
    NT_DEF_PROM_KONEC,
    NT_DEFINICE_FUNKCE,
    NT_SEZNAM_PARAMETRU,
    NT_PARAMETR_PRVNI,
    NT_PARAMETR_DALSI,
    NT_SEZNAM_TERMU,
    NT_TERM_DALSI,
    NT_SLOZENY_PRIKAZ,
    NT_BLOK_PRIKAZU,
    NT_PRIKAZ,
    NT_POUZITI,
    NT_VOLANI_FUNKCE,
    NT_NAVRAT_KONEC,
    NT_PRIRAZENI,
    NT_PRAVA_STRANA,
    NT_NAVRATOVY_TYP,
    NT_DOLLAR // Vzdy posledni
}NTType;

/* Non-terminal */
typedef struct {
    NTType type;
}NT;

/* Get appropriate rule number from TT table - based on non-terminal and token */
int getRuleNumber(NT *nt, Ttoken *token);

#endif // include guard
