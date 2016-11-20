#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "stack.h"
#include "ial.h"


typedef struct sFrame {
	struct sFrame *parent;
	struct sFrame *child;
	unsigned int size;
	Data *data; //parametry a promenne
}StackFrame;

Data *findInFrame(char *name, StackFrame *sf);
StackFrame *newFrame(StackFrame *parent, void *ts);
void deleteFrame(StackFrame *sf);

#endif // include guard
