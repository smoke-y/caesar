#pragma once

#include "../c.h"

#define IDT_MAX_INTR 255

ENUM{
	/*
	 *	task gates:     hardware task switch to task state segment. Not used as it is slow
	 *	interrupt gate: disable interrupts to prevent re-enterance. Used for hardware interrupts
	 *	trap gate:      interrupts are enabled and re-enterance is possible. Software interrupts
	*/
	IDT_GATE_TASK    = 0x5,
	IDT_GATE_INTR_16 = 0x6,
	IDT_GATE_TRAP_16 = 0x7,
	IDT_GATE_INTR_32 = 0xE,
	IDT_GATE_TRAP_32 = 0xF,
} IDTGateType;
ENUM{
	IDT_DPL_HIGH = 0x0,
	IDT_DPL_MID  = 0x1,
	IDT_DPL_LOW  = 0x2
} IDTDPLPrivilege;
STRUCT{
	u64 offsetLow  : 16;
	u64 segment    : 16;
	u64 _reserved1 : 8;
	u64 gateType   : 4;
	u64 _reserved2 : 1;
	u64 dpl        : 2;
	u64 p          : 1;
	u64 offsetHigh : 16;
} IDTEntry;
