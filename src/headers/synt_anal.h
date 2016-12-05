#ifndef SYNT_ANAL_H
#define SYNT_ANAL_H

#include <stdbool.h>
#include <string.h>
#include "collections.h"
#include "error.h"

extern cQueue token_archive;
extern cStack stack;

/* Get appropriate rule number from TT table - based on non-terminal and terminal */
int getRuleNumber(NTType nt, TType t);

/* Apply rule identified by number to stack (= expand non-terminal) */
void applyRule(int rule, cStack *stack);

/* Get next terminal (from getNextToken() OR token archive) */
Terminal getNextTerminal();

/* Get appropriate rule number from TT table - based on non-terminal and terminal */
char getPrecedenceOperation(PType p, TType t);

/* Get next precedence symbol (from getNextToken() OR token archive) */
Psymbol getNextPrecSymbol();

/* Apply precedence operation identified by its character to stack */
void applyPrecedenceOperation(char operation, cStack *stack);

/* Auxiliary function to push terminal on stack (token will be NULL) */
void push_terminal(TType type, cStack *stack);

/* Auxiliary function to push non-terminal on stack */
void push_nonterminal(NTType type, cStack *stack);

/* Auxiliary function to push precedence symbol on stack */
void push_psymbol(PType type, cStack *stack);

/* Run precedence analysis */
void prec_analysis(Ttoken *token);

/* Run syntax analysis */
void execute();

#endif  include guard
