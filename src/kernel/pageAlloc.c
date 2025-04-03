#include "../c.h"
#include "../libc/libc.h"
#include "pageAlloc.h"
#include "tty.h"

u32 alignDown(u32 num, u32 alignment){ return num & ~(alignment - 1); };
u32 alignUp(u32 num, u32 alignment){ return (num + alignment - 1) & ~(alignment - 1); };

void initPageAlloc(multiboot_info_t *info, PageAllocContext *context){
	/*
	 * mem_upper tells us the story after 1MB. Since the kernel is loaded at 2MB we don't have to worry
	 * mem_lower which tells the number of pages below 1MB. kernel_start and kernel_end is defined in boot.S
	*/
	extern void *kernel_start, *kernel_end;
	u32 kernelEndAlign = alignUp((u32)&kernel_end, PAGE_SIZE);
	u32 totalAvailRam = (info->mem_upper * 1024) - (kernelEndAlign - alignDown((u32)&kernel_start, PAGE_SIZE));
	context->pageCount = totalAvailRam / PAGE_SIZE;
	context->bitmaps = (u32*)kernelEndAlign;
	memset((void*)kernelEndAlign, 0, PAGE_SIZE);
};
void *allocPage(PageAllocContext *context){
	char *starting = (char*)((char*)context->bitmaps + PAGE_SIZE);
	u32 flag = ~0;
	for(u32 x=0; x<context->pageCount; x++){
		if(flag ^ context->bitmaps[x]){
			u32 off = 0;
			u32 bit = context->bitmaps[x];
			while(IS_BIT(bit, off)) off++;
			SET_BIT(context->bitmaps[x], off);
			return starting + PAGE_SIZE*(x + off);
		};
	};
	kprint("[ERROR]: no more free pages left :(\n");
	return nullptr;	
};
void freePage(void *ptr, PageAllocContext *context){
	u32 starting = (u32)((char*)context->bitmaps + PAGE_SIZE);
	u32 mem = (u32)ptr;
	u32 off = (mem - starting) / (PAGE_SIZE);
	u32 st = off / 32;						//floors it automatically
	CLR_BIT(context->bitmaps[st], (off - st)); 
};
