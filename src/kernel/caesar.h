#include "../c.h"
#include "tty.h"
#include "pageAlloc.h"
#include "gdt.h"

STRUCT{
	TTY tty; 
	PageAllocContext pageAllocContext;
} Caesar;
