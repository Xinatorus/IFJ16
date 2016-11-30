#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <stdbool.h>
#include "lex_anal.h"
#include "synt_structures.h"

/* Token archive - used in syntax analysis */
extern Ttoken *archive;

////////////////////////////
/////////// ITEM ///////////
////////////////////////////

typedef enum {
    IT_ERROR,
    IT_TERMINAL,
    IT_NTTYPE,
    IT_PSYMBOL
}cItemType;

typedef union {
    int error;
    Terminal terminal;
    NTType nttype;
    Psymbol psymbol;
}cItemData;

typedef struct {
    // Type of stored data
    cItemType type;
    // Data (any type from cItemData union)
    cItemData content;
}cItem;

/////////////////////////////
/////////// STACK ///////////
/////////////////////////////

typedef struct {
    unsigned cap; // Capacity
    unsigned used; // Used capacity
    cItem *items; // Items
}cStack;

// Init stack with custom size
bool cStack_init(cStack *stack, unsigned size);
// Free stack and its items
void cStack_free(cStack *stack);
// Insert item into stack
bool cStack_push(cStack *stack, cItem item);
// Remove item from the stack top
bool cStack_pop(cStack *stack);
// Receive copy of item from the stack top (when empty: item.type = T_ERROR)
cItem cStack_top(cStack *stack);
// Check whether the stack is empty
bool cStack_isempty(cStack *stack);

#endif // include guard