#include "../c.h"

#include "pageAlloc.h"
#include "tty.h"
#include "caesar.h"
#include "multiboot.h"

#include "pageAlloc.c"

static Caesar caesar;
extern void *kernel_start, *kernel_end;
TTY *tty = &caesar.tty;

void caesar_main(multiboot_info_t *info, u32 magicNum){
	initPageAlloc(info, &caesar.pageAllocContext);
	void *ttyBuff = allocPage(&caesar.pageAllocContext);
	ttyInit(ttyBuff, VGA_COLOR_WHITE, VGA_COLOR_BLACK);

	if(magicNum != MULTIBOOT_BOOTLOADER_MAGIC){
		kprint("[-] magic number not verified(%d != %d)\n", magicNum, MULTIBOOT_BOOTLOADER_MAGIC);
		return;
	}else kprint("[+] multiboot magic number verified\n");

	kprint("[+] kernel_start: %p  kernel_end: %p\n", &kernel_start, &kernel_end);
	kprint("[+] page start: %p  page count: %d  tty using 1 page: %p\n", caesar.pageAllocContext.bitmaps, caesar.pageAllocContext.pageCount, ttyBuff);
};
