#pragma once

#include "../c.h"

#define CODE_SEG 0x08
#define DATA_SEG 0x10

ENUM{
	GDT_ACCESS    = 1<<0,   //CPU will set this bit to 1 when the segment is accessed
	GDT_RW        = 1<<1,   //code seg[0: read not allowed], data seg[0: write not allowed]
	GDT_DC        = 1<<2,   //direction/conforming. data seg[0: offset increases]
		                //code seg[0: only executed if privilege level matches, 1: executes only when CPL >= DPL]
	GDT_E         = 1<<3,   //0: data segment, 1: code segment
	GDT_S         = 1<<4,   //0: system segment(tss segment), 1: code/data segment

	GDT_DPL_HIGH  = 0,      //privilege level of segment 
	GDT_DPL_MID   = 1<<5,
	GDT_DPL_LOW   = 2<<5,

	GDT_P         = 1<<7,   //must be 1 for any valid segment
} GDTAccess;
ENUM{
	GDT_FLAG_G_KIB  = 1<<3,  //segment granularity: kibibyte(2^10 bytes or 1024 bytes)
	GDT_FLAG_DB_32  = 1<<2, //0: 16-bit protected segment, 1: 32-bit protected segment
	GDT_FLAG_L      = 1<<1, //1: 64-bit segment
} GDTFlags;

STRUCT{
	u64 limitLow  : 16;
	u64 baseLow   : 24;
	u64 access    : 8;
	u64 limitHigh : 4;
	u64 flags     : 4;
	u64 baseHigh  : 8;
} __attribute__((packed)) GDTEntry;
