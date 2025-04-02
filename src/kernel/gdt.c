#include "gdt.h"
#include "tty.h"

#define GDT_ENTRY(base, limit, acc, flag){	\
	((u32)(limit) & 0x0000FFFF),		\
	((u32)base & 0x00FFFFFF),		\
	(acc),					\
	(((u32)(limit) & 0xFFFF0000) >> 16),	\
	(flag),					\
	(((u32)base & 0xFF000000) >> 24),	\
	}					\

#define GDT_ENTRY_COUNT 3

STRUCT{
	u16 limit;
	GDTEntry *entries;
} __attribute__((packed)) GDTR;

void __attribute__((cdecl)) _gdt_load_cpu(GDTR *gdtr, u16 codeSeg, u16 dataSeg);
void createGDT(){
	extern void *data_start, *data_end, *code_start, *code_end;
	GDTEntry gdt[GDT_ENTRY_COUNT] = {
		GDT_ENTRY(0, 0, 0, 0),
		/*
		 * flat memory layout. Let vitual memory handle
		 * memory permission as it is more faster than
		 * reloading segment registers
		*/
		GDT_ENTRY(0x0, 0xFFFFF, GDT_P | GDT_DPL_HIGH | GDT_S | GDT_E | GDT_RW, GDT_FLAG_G_KIB | GDT_FLAG_DB_32),
		GDT_ENTRY(0x0, 0xFFFFF, GDT_P | GDT_DPL_HIGH | GDT_S | GDT_RW, GDT_FLAG_G_KIB | GDT_FLAG_DB_32),
	};
	kprint("---------[GDT]---------\n");
	for(u32 x=0; x<GDT_ENTRY_COUNT; x++){
		GDTEntry entry = gdt[x];
		u32 base = (u32)entry.baseLow  | (u32)entry.baseHigh<<24;
		u32 size = (u32)entry.limitLow | (u32)entry.limitHigh<<16;
		u32 flag = (u32)entry.flags;
		u32 acc  = (u32)entry.access;
		kprint("%p[%d]  %d  %d\n", base, size, flag, acc);
	};
	GDTR gdtr = {sizeof(gdt)-1, gdt};
	_gdt_load_cpu(&gdtr, 0x08, 0x10);
};
