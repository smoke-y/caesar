#include "idt.h"

IDTEntry idt[IDT_MAX_INTR];

void addIDTEntry(u32 off, void *addrptr, IDTGateType gate, IDTDPLPrivilege priv){
	IDTEntry entry;
	u32 addr = (u32)addrptr;

	entry._reserved1 = 0;
	entry._reserved2 = 0;
	entry.p          = 1;
	entry.offsetLow  = addr & 0x0000FFFF;
	entry.offsetHigh = (addr & 0xFFFF0000) >> 16;
	entry.gateType   = gate;
	entry.dpl        = priv;

	idt[off] = entry;
};

STRUCT{
	u16 count;
	IDTEntry *idt;
} __attribute__((packed)) IDTR;
void __attribute__((cdecl)) _idt_load_cpu(IDTR *idtr);
void loadIDTToCPU(){
	IDTR idtr = {sizeof(IDTEntry)*IDT_MAX_INTR-1, idt};
	_idt_load_cpu(&idtr);
};
