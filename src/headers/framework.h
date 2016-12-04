#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "stack.h"
#include "ial.h"
#include "tstree.h"


typedef struct sFrame {
	char *identifier; // pro vyhledavani?? jmeno fce 
	struct sFrame *parent;
	struct sFrame *child;
	unsigned int size; // nevim proc jsem to tu dal
	Data *data; //parametry a promenne
}StackFrame;

Data *findInFrame(char *name, StackFrame *sf);
StackFrame *newFrame(StackFrame *parent, TsTree root, char *name);
void deleteFrame(StackFrame *sf);




#endif // !FRAMEWORK

