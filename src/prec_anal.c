#include "headers\synt_anal.h"

int prec_rules[14][14] = {
//     i     (     )     +     -     *     /     <     >     <=    >=    ==    !=    $
    { 'X' , 'X' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_VALUE
    { '<' , '<' , '=' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' } , // PS_LRB
    { 'X' , 'X' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , 'X' } , // PS_RRB
    { '<' , '<' , '>' , '>' , '>' , '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_PLUS
    { '<' , '<' , '>' , '>' , '>' , '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_MINUS
    { '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_STAR
    { '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_SLASH
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , '>' } , // PS_LTHAN
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , '>' } , // PS_RTHAN
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , '>' } , // PS_LTHANEQ
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , '>' } , // PS_RTHANEQ
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' , 'X' , '>' } , // PS_EQ
    { '<' , '<' , '>' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' , 'X' , '>' } , // PS_NEQ
    { '<' , 'X' , 'X' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '>' }   // PS_DOLLAR
};

char getPrecedenceOperation(PType p, TType t) {

    return prec_rules[p][t];
}

Psymbol getNextPrecSymbol() {

}


void push_psymbol(PType type, cStack *stack) {
    cItem item;
    Psymbol symbol;
    symbol.token = NULL;
    symbol.type = type;
    item.type = IT_PSYMBOL;
    item.content.psymbol = symbol;
    if (!cStack_push(stack, item)) {
        error(INTER_ERROR);
    }
}

void prec_analysis(Ttoken *token) {
    return;
}