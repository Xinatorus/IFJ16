#include <string.h>
#include "headers\synt_anal.h"
#include "headers\prec_anal.h"
#include "headers\lex_anal.h"
#include "headers\collections.h"
#include "headers\error.h"

int getRuleNumber(NTType nt, TType token) {
    int rules[NT_DOLLAR+1][T_EOF+1] = {
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } ,
        { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
    };

    return rules[nt][token];
}

void applyRule(int rule, Stack *stack) {
    if (stack == NULL) {
        return;
    }
    
    switch (rule) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        case 10:

            break;
        case 11:

            break;
        case 12:

            break;
        case 13:

            break;
        case 14:

            break;
        case 15:

            break;
        case 16:

            break;
        case 17:

            break;
        case 18:

            break;
        case 19:

            break;
        case 20:

            break;
        case 21:

            break;
        case 22:

            break;
        case 23:

            break;
        case 24:

            break;
        case 25:

            break;
        case 26:

            break;
        case 27:

            break;
        case 28:

            break;
        case 29:

            break;
        case 30:

            break;
        case 31:

            break;
        case 32:

            break;
        case 33:

            break;
        case 34:

            break;
        case 35:

            break;
        case 36:

            break;
        case 37:

            break;
        case 38:

            break;
        case 39:

            break;
        case 40:

            break;
        case 41:

            break;
        default:
            break;
    }
}

TType getNextTerminal() {
    static Ttoken *archive = NULL;
    Ttoken *token = NULL;
    // Something is left in token archive, we must use this
    if (archive != NULL) {
        token = archive;
        archive = NULL;
    }
    else {
        token = getNextToken();
    }

    if (token->type == KLICOVE_SLOVO) {
        if (strcmp(token->attr->str, "class") == 0) {
            return T_CLASS;
        }
        if (strcmp(token->attr->str, "static") == 0) {
            return T_STATIC;
        }
        if (strcmp(token->attr->str, "return") == 0) {
            return T_RETURN;
        }
        if (strcmp(token->attr->str, "if") == 0) {
            return T_IF;
        }
        if (strcmp(token->attr->str, "else") == 0) {
            return T_ELSE;
        }
        if (strcmp(token->attr->str, "while") == 0) {
            return T_WHILE;
        }
        if (strcmp(token->attr->str, "void") == 0) {
            return T_VOID;
        }
        if (strcmp(token->attr->str, "int") == 0 && 
            strcmp(token->attr->str, "double") == 0 &&
            strcmp(token->attr->str, "String") == 0) {
            return T_TYPE;
        }
    }
    if (token->type == PRIRAZENI) {
        return T_ASSIGN;
    }
    if (token->type == KONEC_SOUBORU) {
        return T_EOF;
    }
    if (token->type == LEVA_KULATA_ZAVORKA) {
        return T_LPAR;
    }
    if (token->type == PRAVA_KULATA_ZAVORKA) {
        return T_RPAR;
    }
    if (token->type == LEVA_HRANATA_ZAVORKA) {
        return T_LSB;
    }
    if (token->type == PRAVA_HRANATA_ZAVORKA) {
        return T_RSB;
    }
    if (token->type == LEVA_SLOZENA_ZAVORKA) {
        return T_LB;
    }
    if (token->type == PRAVA_SLOZENA_ZAVORKA) {
        return T_RB;
    }
    if (token->type == STREDNIK) {
        return T_SC;
    }
    if (token->type == CARKA) {
        return T_COMMA;
    }
    if (token->type == RETEZEC ||
        token->type == DESETINNY_LITERAL ||
        token->type == DESETINNY_LITERAL_EXPONENT ||
        token->type == CELOCISELNY_LITERAL ||
        token->type == CELOCISELNY_LITERAL_EXPONENT) {
        return T_EXPRESSION;
    }
    // We must decide whether this will be an expression...
    if (token->type == IDENTIFIKATOR ||
        token->type == PLNE_KVALIFIKOVANY_IDENTIFIKATOR) {
        archive = getNextToken(); // We have to use another token
        // identificator followed by operator is surely an expression
        if (archive->type != SCITANI && 
            archive->type != ODECITANI && 
            archive->type != NASOBENI && 
            archive->type != DELENI && 
            archive->type != MENSI &&
            archive->type != VETSI &&
            archive->type != ROVNO &&
            archive->type != NEROVNO &&
            archive->type != MENSI_NEBO_ROVNO &&
            archive->type != VETSI_NEBO_ROVNO) {
            return T_IDENT;
        }
        else {
            return T_EXPRESSION;
        }
    }

    // Other possibilities - like ODECITANi outside expression are not possible
    return T_UNKNOWN;
}

void execute() {
    cStack stack;
    cStack_init(&stack, 50);
    /* First step - push NT_DOLLAR (NT version of EOF) and NT_PROGRAM to stack */
    cItem i01 = { .type = IT_NTTYPE, .content.nttype = NT_DOLLAR };
    cStack_push(&stack, i01);;
    cItem i02 = { .type = IT_NTTYPE, .content.nttype = NT_PROGRAM };
    cStack_push(&stack, i02);

    /* Second step - loop :o */
    TType input= getNextTerminal(); // Actual terminal from input
    cItem top; // Top of the stack
    do {
        top = cStack_top(&stack);

        // We have NT_DOLLAR on top -> success or fail
        if (top.type == IT_NTTYPE && top.content.nttype == NT_DOLLAR) {
            if (input == T_EOF) {
                return;
            }
            else {
                error(SYNTA_ERROR);
            }
        }

        // We have terminal on top -> if it is the same as terminal from input, process
        if (top.type == IT_TTYPE && top.content.ttype == input) {
            // TODO In case of expression run precedence analysis
            cStack_pop(&stack);
            input = getNextTerminal();
        }
        else {
            error(SYNTA_ERROR);
        }

        // We have non-terminal on top -> try to find and apply LL rule
        if (top.type == IT_NTTYPE) {
            // TODO 
        }

    } while (input != T_EOF);
}
