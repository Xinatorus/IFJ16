#ifndef SYNT_STRUCTURES_H
#define SYNT_STRUCTURES_H

// INFO:
// This file exists to break Circular dependency within collections.h and synt_anal.h
// Refer to https://en.wikipedia.org/wiki/Circular_dependency for more details

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
    NT_SEZNAM_VSTUPU,
    NT_VSTUP_DALSI,
    NT_VSTUP_KONEC,
    NT_SLOZENY_PRIKAZ,
    NT_BLOK_PRIKAZU,
    NT_PRIKAZ,
    NT_POUZITI,
    NT_VOLANI_FUNKCE,
    NT_NAVRAT_KONEC,
    NT_PRIRAZENI,
    NT_PRAVA_STRANA,
    NT_DATOVY_TYP,
    NT_DOLLAR
}NTType;

/* List of possible terminals (excluding lex_error and expression symbols) */
typedef enum {
    T_IDENT,        // identificator
    T_FIDENT,       // function identificator
    T_CLASS,        // keyword CLASS
    T_STATIC,       // keyword STATIC
    T_RETURN,       // keyword RETURN
    T_IF,           // keyword IF
    T_ELSE,         // keyword ELSE
    T_WHILE,        // keyword WHILE
    T_VOID,         // keyword VOID
    T_TYPE,         // int, double, String
    T_EXPRESSION,   // any kind of expression - at least 2 tokens (num, variable id, string, parenthesis, aritmetic + relation operators)
    T_LCB,          // {
    T_RCB,          // }
    T_LRB,          // (
    T_RRB,          // )
    T_SC,           // ;
    T_COMMA,        // ,
    T_ASSIGN,       // =
    T_EOF,          // EOF
    T_UNKNOWN       // some other not known terminal
}TType;

typedef struct {
    TType type; // Type of this terminal
    Ttoken *token; // Associated token (can be NULL if it is made form Nonterminal)
}Terminal;

#endif // include guard
