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

void __attribute__((cdecl)) _gdt_load_cpu_and_enable_protected_mode(GDTR *gdtr, u16 codeSeg, u16 dataSeg);
void createGDTAndEnableProtectedMode(){
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
	GDTR gdtr = {sizeof(gdt)-1, gdt};
	_gdt_load_cpu_and_enable_protected_mode(&gdtr, CODE_SEG, DATA_SEG);
};
