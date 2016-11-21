#include "headers/collections.h"

/////////////////////////////
/////////// STACK ///////////
/////////////////////////////

bool cStack_init(cStack *stack, unsigned size) {
    stack->cap = size;
    stack->used = 0;
    stack->items = malloc(sizeof(cItem)*size);
    return (stack->items != NULL);
}

void cStack_free(cStack *stack) {
    free(stack->items);
    free(stack);
}

bool cStack_push(cStack *stack, cItem item) {
    if (stack->used >= stack->cap) {
        cItem *new = realloc(stack->items, sizeof(cItem) * 2 * stack->cap);
        if (new == NULL) {
            return false;
        }
        else {
            stack->items = new;
        }
        stack->cap *= 2;
    }
    stack->items[stack->used++] = item;
    return true;
}

bool cStack_pop(cStack *stack) {
    if (cStack_isempty(stack)) {
        return false;
    }
    else {
        stack->used--;
        return true;
    }
}

cItem cStack_top(cStack *stack) {
    cItem item;
    if (cStack_isempty(stack)) {
        cItem item;
        item.type = T_ERROR;
        item.cdata.error = 1;
        return item;
    }
    return stack->items[stack->used-1];
}

bool cStack_isempty(cStack *stack) {
    return (stack->used == 0);
}