ENTRY(_start)

PHDRS {
    text PT_LOAD FLAGS(5);   /* R-X */
    rodata PT_LOAD FLAGS(4); /* R-- */
    bss PT_LOAD FLAGS(6);    /* RW- */
}

SECTIONS{
	. = 2M;
	kernel_start = .;
	
	.text BLOCK(4K) : ALIGN(4K){
		*(.multiboot)
		*(.text)
	} :text

	.rodata BLOCK(4K) : ALIGN(4K){
		*(.rodata)
	} :rodata


	.bss BLOCK(4K) : ALIGN(4K){
		*(.COMMON)
		*(.bss)
	} :bss

	kernel_end = .;
}
