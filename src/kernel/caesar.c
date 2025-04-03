#include "../c.h"

#include "gdt.h"
#include "pageAlloc.h"
#include "tty.h"
#include "caesar.h"
#include "multiboot.h"

#include "pageAlloc.c"
#include "gdt.c"
#include "idt.c"

static Caesar caesar;
extern void *kernel_start, *kernel_end, *code_start, *code_end, *data_start, *data_end;
TTY *tty = &caesar.tty;

void caesar_main(multiboot_info_t *info, u32 magicNum){
	initPageAlloc(info, &caesar.pageAllocContext);
	void *ttyBuff = allocPage(&caesar.pageAllocContext);
	ttyInit(ttyBuff, VGA_COLOR_WHITE, VGA_COLOR_BLACK);

	if(magicNum != MULTIBOOT_BOOTLOADER_MAGIC){
		kprint("[-] magic number not verified(%d != %d)\n", magicNum, MULTIBOOT_BOOTLOADER_MAGIC);
		return;
	}
	kprint("[+] code_start: %p  code_end: %p\n", &code_start, &code_end);
	kprint("[+] data_start: %p  data_end: %p\n", &data_start, &data_end);
	kprint("[+] page start: %p  page count: %d\n", caesar.pageAllocContext.bitmaps, caesar.pageAllocContext.pageCount);

	createGDT();
	kprint("[+] loaded gdt table to cpu\n");

	loadIDTToCPU();
	kprint("[+] loaded idt table to cpu\n");
};
