#include "../c.h"
#include "tty.h"
#include "pageAlloc.h"

STRUCT{
	TTY tty; 
	PageAllocContext pageAllocContext;
} Caesar;
