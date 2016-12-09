#define _CRT_SECURE_NO_WARNINGS // pro zruseni warningu visual studia
#include "headers\synt_anal.h"

Ttoken *token_param = NULL; // Token got from prec_analysis() call

char prec_rules[17][17] = {
//     i    ESYS   (     )     +     -     *     /     <     >     <=    >=    ==    !=   LSYS  RSYS   $
    { 'X' , 'X' , 'X' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , 'X' , 'X' , '>' } , // PS_VALUE
    { 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' } , // PS_ESYS
    { '<' , 'X' , '<' , '=' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' } , // PS_LRB
    { 'X' , 'X' , 'X' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , 'X' , 'X' , '>' } , // PS_RRB
    { '<' , 'X' , '<' , '>' , '>' , '>' , '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , 'X' , 'X' , '>' } , // PS_PLUS
    { '<' , 'X' , '<' , '>' , '>' , '>' , '<' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , 'X' , 'X' , '>' } , // PS_MINUS
    { '<' , 'X' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , 'X' , 'X' , '>' } , // PS_STAR
    { '<' , 'X' , '<' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , '>' , 'X' , 'X' , '>' } , // PS_SLASH
    { '<' , 'X' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , 'X' , 'X' , '>' } , // PS_LTHAN
    { '<' , 'X' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , 'X' , 'X' , '>' } , // PS_RTHAN
    { '<' , 'X' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , 'X' , 'X' , '>' } , // PS_LTHANEQ
    { '<' , 'X' , '<' , '>' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' , '>' , 'X' , 'X' , '>' } , // PS_RTHANEQ
    { '<' , 'X' , '<' , '>' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' } , // PS_EQ
    { '<' , 'X' , '<' , '>' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'X' , 'X' , '>' } , // PS_NEQ
    { 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' } , // PS_LSYS
    { 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' } , // PS_RSYS
    { '<' , 'X' , '<' , 'X' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , '<' , 'X' , 'X' , 'E' }   // PS_DOLLAR
};

char getPrecedenceOperation(PType top, PType input) {

    #if PREC_DEBUG == 1
        fprintf(stdout, "  [PREC_DEBUG] getPrecedenceOperation(%s, %s)\n", PType_string[top], PType_string[input]);
    #endif

    return prec_rules[top][input];
}

Psymbol getNextPrecSymbol() {
    static int par_level = 0; // Level of parenthesis

    Ttoken *token = NULL; // Token to work with
    Psymbol symbol; // Symbol to return

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
        token = load_next_token();
    }

    symbol.token = token;
    symbol.type = PS_DOLLAR;
    symbol.data = '-';

    if (token->type == IDENTIFIKATOR ||
        token->type == PLNE_KVALIFIKOVANY_IDENTIFIKATOR) {

        /* @SEM2 - Check for variables declaration (in expr) inside functions */
        if (!first_analysis && strlen(current_func) > 0) {
            if (get_declared_variable(token->attr->str, current_class, current_func) == NULL) {
                #if SEM_DEBUG == 1
                    fprintf(stdout, "\t@ User tried to use undeclared variable (in expr) %s in function %s!\n", token->attr->str, current_func);
                #endif
                error(ERR_SEM_DEF);
            }
        }
        /* @SEM1 - Check for variables declaration (in expr) in static context */
        if (first_analysis && strlen(current_func) == 0) {
            if (get_declared_variable(token->attr->str, current_class, NULL) == NULL) {
                #if SEM_DEBUG == 1
                    fprintf(stdout, "\t@ User tried to use undeclared variable (in expr) %s in static context of class %s!\n", token->attr->str, current_class);
                #endif
                error(ERR_SEM_DEF);
            }
        }

        /* @SEM2 - Get data type from identificator */
        if (!first_analysis) {
            symbol.data = get_declared_variable(token->attr->str, current_class, current_func)->type[1];
        }
    }

    /* @SEM2 - Get data type from value */
    if (!first_analysis) {
        if (token->type == RETEZEC)
            symbol.data = 'S';
        else if (token->type == CELOCISELNY_LITERAL || token->type == CELOCISELNY_LITERAL_EXPONENT)
            symbol.data = 'I';
        else if (token->type == DESETINNY_LITERAL || token->type == DESETINNY_LITERAL_EXPONENT)
            symbol.data = 'D';
    }

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

void push_cstack_psymbol(PType type, cStack *stack, char data) {
    cItem item;
    Psymbol symbol;
    symbol.token = NULL;
    symbol.type = type;
    symbol.data = data;
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
    #if PREC_DEBUG == 1
        fprintf(stdout, "  [PREC_DEBUG]   === PRECEDENCE ANALYSIS STARTED ===\n");
    #endif

    token_param = token; // We need to process this first

    // First step - there is T_EXPRESSION on top, pop it
    cStack_pop(&stack);
    // Second step - push $ on top
    push_cstack_psymbol(PS_DOLLAR, &stack, '-');

    char operation;
    Psymbol input = getNextPrecSymbol();
    cItem top;
    cStack temporary; // Because we need sometimes to read prec.symbol more deeply from stack
    cStack_init(&temporary, 5);
    do {
        #if PREC_DEBUG == 1
            fprintf(stdout, "    - - -\n");
        #endif

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
            push_cstack_psymbol(top.content.psymbol.type, &temporary, top.content.psymbol.data);
            cStack_pop(&stack);
            top = cStack_top(&stack);
        }
        // Finally get precedence operation
        operation = getPrecedenceOperation(top.content.psymbol.type, input.type);
        if (operation != '<') {
            // We have to push everything "borrowed" back (the check for < is there because operation < does it by itself)
            while (!cStack_isempty(&temporary)) {
                push_cstack_psymbol(cStack_top(&temporary).content.psymbol.type, &stack, cStack_top(&temporary).content.psymbol.data);
                cStack_pop(&temporary);
                top = cStack_top(&stack);
            }
        }

        #if PREC_DEBUG == 1
            fprintf(stdout, "  [PREC_DEBUG]  Operation = '%c'\n", operation);
        #endif

        /* Apply operation */
        if (operation == '<') {
            push_cstack_psymbol(PS_LSYS, &stack, '-'); // This is pushed just after non-SYS prec. symbol
            // We have to push everything "borrowed" back
            while (!cStack_isempty(&temporary)) {
                push_cstack_psymbol(cStack_top(&temporary).content.psymbol.type, &stack, cStack_top(&temporary).content.psymbol.data);
                cStack_pop(&temporary);
                top = cStack_top(&stack);
            }
            push_cstack_psymbol(input.type, &stack, input.data);
            input = getNextPrecSymbol();
        }
        else if (operation == '>') {

            // (E) -> E
            if (top.content.psymbol.type == PS_RRB) { // )>
                cStack_pop(&stack);
                top = cStack_top(&stack);
                if (top.content.psymbol.type == PS_ESYS) { // E)>
                    cStack_pop(&stack);
                    top = cStack_top(&stack);
                    if (top.content.psymbol.type == PS_LRB) { // (E)>
                        cStack_pop(&stack);
                        top = cStack_top(&stack);
                        if (top.content.psymbol.type == PS_LSYS) { // <(E)>
                            cStack_pop(&stack);
                            top = cStack_top(&stack);
                            push_cstack_psymbol(PS_ESYS, &stack, '-'); // <(E)> -> E
                        }
                        else error(ERR_SYNT);
                    }
                    else error(ERR_SYNT);
                }
                else error(ERR_SYNT);
            }
            // i -> E
            else if (top.content.psymbol.type == PS_VALUE) { // i>
                cStack_pop(&stack);
                top = cStack_top(&stack);
                if (top.content.psymbol.type == PS_LSYS) { // <i>
                    cStack_pop(&stack);
                    top = cStack_top(&stack);
                    push_cstack_psymbol(PS_ESYS, &stack, '-'); // <i> -> E
                }
                else error(ERR_SYNT);
            }
            // E op E -> E
            else if (top.content.psymbol.type == PS_ESYS) { // E>
                cStack_pop(&stack);
                top = cStack_top(&stack);
                if (top.content.psymbol.type == PS_PLUS || 
                    top.content.psymbol.type == PS_MINUS || 
                    top.content.psymbol.type == PS_STAR || 
                    top.content.psymbol.type == PS_SLASH || 
                    top.content.psymbol.type == PS_LTHAN || 
                    top.content.psymbol.type == PS_RTHAN || 
                    top.content.psymbol.type == PS_LTHANEQ || 
                    top.content.psymbol.type == PS_RTHANEQ || 
                    top.content.psymbol.type == PS_EQ || 
                    top.content.psymbol.type == PS_NEQ) { // op E>
                    cStack_pop(&stack);
                    top = cStack_top(&stack);
                    if (top.content.psymbol.type == PS_ESYS) { // E op E>
                        cStack_pop(&stack);
                        top = cStack_top(&stack);
                        if (top.content.psymbol.type == PS_LSYS) { // <E op E>
                            cStack_pop(&stack);
                            top = cStack_top(&stack);
                            push_cstack_psymbol(PS_ESYS, &stack, '-'); // <E op E> -> E
                        }
                        else error(ERR_SYNT);
                    }
                    else error(ERR_SYNT);
                }
                else error(ERR_SYNT);
            }
            else error(ERR_SYNT);

        }
        else if (operation == '=') {
            push_cstack_psymbol(input.type, &stack, input.data);
            input = getNextPrecSymbol();
        }
        else if (operation != 'E') {
            // Unknown operation? X = error
            error(ERR_SYNT);
        }

    } while (operation != 'E');

    // Now, there should be $E on the top
    if (top.type != IT_PSYMBOL || top.content.psymbol.type != PS_ESYS) {
        error(ERR_SYNT);
    }
    cStack_pop(&stack);
    top = cStack_top(&stack);
    // Now, there should be $ on the top
    if (top.type != IT_PSYMBOL || top.content.psymbol.type != PS_DOLLAR) {
        error(ERR_SYNT);
    }
    cStack_pop(&stack);


    cStack_free(&temporary);

    #if PREC_DEBUG == 1
        fprintf(stdout, "  [PREC_DEBUG]   === PRECEDENCE ANALYSIS FINISHED ===\n");
    #endif

    return;
}
