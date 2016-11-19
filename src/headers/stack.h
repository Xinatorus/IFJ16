#ifndef STACK
#define STACK

typedef struct {
	char *name;
	enum {
		t_int,
		t_double,
		t_string,
	}type;
	union {
		int v_int;
		double v_double;
		char *v_string;
	}value;
}Data;

typedef struct {
	unsigned int size;
	unsigned int SP; // index vrcholu
	unsigned int BP; // base pointer
	Data *data;
}Stack;


Stack stackInit(unsigned int size);
void stackFree(Stack stack);
int stackPush(Stack stack, Data data);
int stackPop(Stack stack, Data *data);
int stackResize(Stack stack, unsigned int newSize);


#endif // !STACK
