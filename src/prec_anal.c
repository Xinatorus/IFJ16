#define _CRT_SECURE_NO_WARNINGS // pro zruseni warningu visual studia
#include "headers\synt_anal.h"

Ttoken *token_param = NULL; // Token got from prec_analysis() call

int prec_rules[14][14] = {
//     i     (     )     +     -     *     /     <     >     <=    >=    ==    !=    $
    { 'X' , 'X' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_VALUE
    { '<' , '<' , '=' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' } , // PS_LRB
    { 'X' , 'X' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' } , // PS_RRB
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
    { '<' , '<' , 'X' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '>' }   // PS_DOLLAR
};

char getPrecedenceOperation(PType top, PType input) {

    return prec_rules[top][input];
}

Psymbol getNextPrecSymbol() {
    Ttoken *token = NULL; // Token to work with
    Psymbol symbol; // Symbol to return
    static int par_level = 0; // Level of parenthesis

    // We got token prec_analysis() call
    if (token_param != NULL) {
        token = token_param;
        token_param = NULL;
    }
    // Something is left in token archive, we must use that
    else if (!cQueue_isempty(&token_archive)) {
        token = cQueue_first(&token_archive).content.token;
        cQueue_pop(&token_archive);
    }
    // Read token from input
    else {
        token = getNextToken();
    }

    symbol.token = token;
    symbol.type = PS_DOLLAR;

    if (token->type == IDENTIFIKATOR ||
        token->type == PLNE_KVALIFIKOVANY_IDENTIFIKATOR ||
        token->type == RETEZEC ||
        token->type == CELOCISELNY_LITERAL ||
        token->type == CELOCISELNY_LITERAL_EXPONENT ||
        token->type == DESETINNY_LITERAL ||
        token->type == DESETINNY_LITERAL_EXPONENT) {
        symbol.type = PS_VALUE;
    }
    else if (token->type == LEVA_KULATA_ZAVORKA) {
        symbol.type = PS_LRB;
        par_level++;
    }
    else if (token->type == PRAVA_KULATA_ZAVORKA) {
        if (par_level > 0) { // Only if not in inner parenthesis level
            symbol.type = PS_RRB;
            par_level--;
        }
    }
    else if (token->type == SCITANI) {
        symbol.type = PS_PLUS;
    }
    else if (token->type == ODECITANI) {
        symbol.type = PS_MINUS;
    }
    else if (token->type == NASOBENI) {
        symbol.type = PS_STAR;
    }
    else if (token->type == DELENI) {
        symbol.type = PS_SLASH;
    }
    else if (token->type == MENSI) {
        symbol.type = PS_LTHAN;
    }
    else if (token->type == VETSI) {
        symbol.type = PS_RTHAN;
    }
    else if (token->type == MENSI_NEBO_ROVNO) {
        symbol.type = PS_LTHANEQ;
    }
    else if (token->type == VETSI_NEBO_ROVNO) {
        symbol.type = PS_RTHANEQ;
    }
    else if (token->type == ROVNO) {
        symbol.type = PS_EQ;
    }
    else if (token->type == NEROVNO) {
        symbol.type = PS_NEQ;
    }

    // We are ending precedence analysis - put unused token back
    if (symbol.type == PS_DOLLAR) {
        insert_cqueue_token(token, &token_archive);
    }

    return symbol;
}

void push_cstack_psymbol(PType type, cStack *stack) {
    cItem item;
    Psymbol symbol;
    symbol.token = NULL;
    symbol.type = type;
    item.type = IT_PSYMBOL;
    item.content.psymbol = symbol;
    if (!cStack_push(stack, item)) {
        error(ERR_INTER);
    }
}

void insert_cqueue_token(Ttoken *token, cQueue *queue) {
    cItem to_insert;
    to_insert.content.token = token;
    to_insert.type = IT_TOKEN;
    cQueue_insert(queue, to_insert);
}

void prec_analysis(Ttoken *token) {
    token_param = token; // We need to process this first

    // First step - push $ on top
    push_cstack_psymbol(PS_DOLLAR, &stack);

    char operation;
    Psymbol input = getNextPrecSymbol();
    cItem top;
    cStack temporary; // Because we need sometimes to read prec.symbol more deeply from stack
    cStack_init(&temporary, 5);
    do {
        top = cStack_top(&stack);
        if (top.type == IT_ERROR) {
            error(ERR_INTER);
        }

        // We HAVE TO have prec. symbol on the top
        if (top.type != IT_PSYMBOL) {
            error(ERR_SYNT);
        }

        // There could be PS_ESYS, PS_LSYS or PS_RSYS on top, in that case we are popping until we find regular prec. symbol to get prec. operation
        while (top.content.psymbol.type == PS_ESYS || top.content.psymbol.type == PS_LSYS || top.content.psymbol.type == PS_RSYS) {
            push_cstack_psymbol(top.content.psymbol.type, &temporary);
            cStack_pop(&stack);
            top = cStack_top(&stack);
        }
        // Finally get precedence operation
        operation = getPrecedenceOperation(top.content.psymbol.type, input.type);
        // We have to push everything "borrowed" back
        while (!cStack_isempty(&temporary)) {
            push_cstack_psymbol(cStack_top(&temporary).content.psymbol.type, &stack);
            cStack_pop(&temporary);
            top = cStack_top(&stack);
        }

        /* Apply operation */
        if (operation == '<') {
            push_cstack_psymbol(PS_LSYS, &stack);
            push_cstack_psymbol(input.type, &stack);
            input = getNextPrecSymbol();
        }
        else if (operation == '>') {

            // pushni PS_RSYS do stacku - to vlastne neni treba, nedelej to
            // popuj stack, postupuj ve stavovem automatu az dojdes k PS_LSYS
            // podle typu stavoveho automatu proved push leve strany pravidla
            // stavovy automat detekuje neplatne (chybove) stavy
        }
        else if (operation == '=') {
            push_cstack_psymbol(input.type, &stack);
            input = getNextPrecSymbol();
        }
        else {
            // Unknown operation? X = error
            error(ERR_SYNT);
        }

    } while (input.type != PS_DOLLAR);


    cStack_free(&temporary);

    return;
}
