.global _gdt_load_cpu
_gdt_load_cpu:
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
    ret
