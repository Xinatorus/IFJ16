#ifndef FRAMEWORK
#define FRAMEWORK

#include "stack.h"
#include "ial.h"


typedef struct sFrame{
	struct sFrame *parent;
	struct sFrame *child;
	unsigned int size;
	Data *ret; // adresa kam se ulozi vysledek
	Data *data; //parametry a promenne
}StackFrame;

Data *findInFrame(char *name, StackFrame sf);
StackFrame *newFrame(char *name, StackFrame parent, void *ts);
void deleteLastFrame(StackFrame sf);

#endif // !FRAMEWORK
