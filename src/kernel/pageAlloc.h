#pragma once

#include "../c.h"
#include "multiboot.h"

#define PAGE_SIZE 1024
STRUCT{
	u32 *bitmaps;
	u32  pageCount;
} PageAllocContext;

u32 alignDown(u32 num, u32 alignment);
u32 alignUp(u32 num, u32 alignment);
void initPageAlloc(multiboot_info_t *info, PageAllocContext *context);
void *allocPage(PageAllocContext *context);
void freePage(void *ptr, PageAllocContext *context);
