#ifndef SYNT_ANAL_H
#define SYNT_ANAL_H

#include <stdbool.h>
#include "lex_anal.h"
#include "collections.h"

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
    NT_SEZNAM_VYRAZU,
    NT_VYRAZ_DALSI,
    NT_SLOZENY_PRIKAZ,
    NT_BLOK_PRIKAZU,
    NT_PRIKAZ,
    NT_POUZITI,
    NT_VOLANI_FUNKCE,
    NT_NAVRAT_KONEC,
    NT_PRIRAZENI,
    NT_PRAVA_STRANA,
    NT_NAVRATOVY_TYP,
    NT_DOLLAR
}NTType;

/* List of possible terminals (excluding lex_error and expression symbols) */
typedef enum {
    T_IDENT,        // identificator
    T_CLASS,        // keyword CLASS
    T_STATIC,       // keyword STATIC
    T_RETURN,       // keyword RETURN
    T_IF,           // keyword IF
    T_ELSE,         // keyword ELSE
    T_WHILE,        // keyword WHILE
    T_VOID,         // keyword VOID
    T_TYPE,         // int, double, String
    T_EXPRESSION,   // any kind of expression (num, variable, string, (, ), +, -, *, /, <, >, <=, >=, ==, !=)
    T_LB,           // {
    T_RB,           // }
    T_LSB,          // [
    T_RSB,          // ]
    T_LPAR,         // (
    T_RPAR,         // )
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

/* Get appropriate rule number from TT table - based on non-terminal and terminal */
int getRuleNumber(NTType nt, TType t);

/* Apply rule identified by number to stack (= expand non-terminal) */
void applyRule(int rule, cStack *stack);

/* Get next terminal (from getNextToken() OR token archive) */
Terminal getNextTerminal();

/* Auxiliary function to push terminal on stack (token will be NULL) */
void push_terminal(TType type, cStack *stack);

/* Auxiliary function to push non-terminal on stack */
void push_nonterminal(NTType type, cStack *stack);

void execute();

#endif // include guard
