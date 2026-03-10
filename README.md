## caeser

A kernel targeting x86 architecture.

### BUILD
You will need to download `i686-elf` toolchain and `qemu-system-i386` vm.<br>
Clone the repo and run `build.py` which will compile C and ASM code to a kernel image. Then run `run.sh` to run the kernel
on qemu vm.

### FEATURES
<ul>
    <li>tty drivers for a console</li>
    <li>memory and page allocation</li>
    <li>interrupt handling</li>
    <li>C lib written from scratch</li>
    <li>supports multiboot</li>
</ul>
