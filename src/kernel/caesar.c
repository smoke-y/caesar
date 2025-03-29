#include "../c.h"

#include "pageAlloc.h"
#include "tty.h"
#include "caesar.h"
#include "multiboot.h"

#include "pageAlloc.c"

static Caesar caesar;
TTY *tty = &caesar.tty;

void caesar_main(multiboot_info_t *info, u32 magicNum){
	initPageAlloc(info, &caesar.pageAllocContext);
	void *ttyBuff = allocPage(&caesar.pageAllocContext);
	ttyInit(ttyBuff, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	if(magicNum != MULTIBOOT_BOOTLOADER_MAGIC){
		putChar('n');
	}else{
		kprint("Hello, world %d\n%d", 47, 48);	
	};
};
