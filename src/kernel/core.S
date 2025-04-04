.set ALIGN,       1<<0   		//align all the modules
.set MEMINFO,     1<<1   		//pass the memory map to us
.set FLAGS,       ALIGN | MEMINFO
.set MAGIC,       0x1BADB002
.set CHECKSUM,    -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384                 		//16Kb
stack_top:

.section .text
.global _start
.type _start, @function
_start:

mov $stack_top, %esp
push %eax  				//push magic number
push %ebx				//push memory map

call caesar_main
cli
1: hlt
jmp 1b

.size _start, . - _start

.global _gdt_load_cpu_and_enable_protected_mode
.global _idt_load_cpu

_gdt_load_cpu_and_enable_protected_mode:
    	pushl %ebp
    	movl %esp, %ebp

    /*
        Higher Addresses
        | ...          |
        | dataSegment  |  16(%ebp) (2 bytes, padded to 4)
        | codeSegment  |  12(%ebp) (2 bytes, padded to 4)
        | descriptor   |  8(%ebp)  (4 bytes, pointer to GDTR)
        | Return Addr  |  4(%ebp)  (4 bytes)
        | Old EBP      |  (%ebp)   (4 bytes)
        | ...          |
        Lower Addresses
    */
    	movl 8(%ebp), %eax
    	lgdt (%eax)
	cli
	movl %cr0, %eax
	or %al, 1
	movl %eax, %cr0

    	movl 12(%ebp), %eax
    	pushl %eax
    	pushl $.reload_ds
    	lret                    # pops eip and cs
.reload_ds:
	movw 16(%ebp), %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss

	movl %ebp, %esp
	popl %ebp
	sti
	ret

_idt_load_cpu:
	pushl %ebp
    	movl %esp, %ebp

	movl 8(%ebp), %eax
	lidt (%eax)

	movl %ebp, %esp
	popl %ebp
	ret
