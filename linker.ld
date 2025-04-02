ENTRY(_start)

PHDRS {
    text PT_LOAD FLAGS(5);   /* R-X */
    rodata PT_LOAD FLAGS(4); /* R-- */
    bss PT_LOAD FLAGS(6);    /* RW- */
}

SECTIONS{
	. = 2M;
	kernel_start = .;
	
	code_start = .;
	.text BLOCK(4K) : ALIGN(4K){
		*(.multiboot)
		*(.text)
	} :text
	code_end = .;

	data_start = .;
	.rodata BLOCK(4K) : ALIGN(4K){
		*(.rodata)
	} :rodata
	.bss BLOCK(4K) : ALIGN(4K){
		*(.COMMON)
		*(.bss)
	} :bss
	data_end = .;

	kernel_end = .;
}
