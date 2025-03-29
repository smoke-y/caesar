#include "../c.h"

#include "tty.h"
#include "caesar.h"
#include "multiboot.h"

#include "pageAlloc.c"

static Caesar caesar;

void caesar_main(multiboot_info_t *info, u32 magicNum){
	initPageAlloc(info, &caesar.pageAllocContext);
	ttyInit(VGA_COLOR_WHITE, VGA_COLOR_BLACK, &caesar.tty);
	if(magicNum != MULTIBOOT_BOOTLOADER_MAGIC){
		putChar('n', &caesar.tty);
	}else{
		for(u32 i=0; i<VGA_WIDTH; i++)putChar('i', &caesar.tty);
		putChar('w', &caesar.tty);
	};
};
