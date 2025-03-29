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
