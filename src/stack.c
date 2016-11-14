#include "headers\stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack stackInit(unsigned int size) {
	Stack stack;
	stack.size = size;
	stack.SP = 0;
	stack.BP = 0;
	stack.data = malloc(sizeof(Data)*size);
}

void stackFree(Stack stack) {
	free(stack.data);
}

int stackPush(Stack stack, Data data) {
	if (stack.SP < stack.size) {
		stack.data[stack.SP++] = data;
		return 0;
	}	
	else return 1;
}

int stackPop(Stack stack, Data *data) {
	if (stack.SP > stack.BP) {
		data->type = stack.data[stack.SP].type;
		data->value = stack.data[stack.SP].value;
		stack.SP--;
		return 0;
	}
	else return 1; 
}
