#ifndef COLLECTIONS.H
#define COLLECTIONS.H

#include "lex_anal.h"
#include <stdbool.h>

////////////////////////////
/////////// ITEM ///////////
////////////////////////////

typedef struct {
    // Type of stored data
    enum {
        T_ERROR,
        T_TOKEN
    }type;

    // Data (any of these types)
    union {
        int error;
        Ttoken token;
    }cdata;
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