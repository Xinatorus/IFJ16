#ifndef VALGRIND_H
#define VALGRIND_H

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC 1
#include <stdlib.h>
#include <Crtdbg.h>
#define malloc(size) _malloc_dbg(size,_CLIENT_BLOCK,__FILE__,__LINE__)
#define free(addr) _free_dbg(addr,_CLIENT_BLOCK)
#endif

void valgrind();

#endif // !VALGRIND_H

