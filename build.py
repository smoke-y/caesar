TOOL_NAME = "i686-elf"
TOOL_PATH = "tools/" + TOOL_NAME + "/bin/"

AS   = "./" + TOOL_PATH + TOOL_NAME + "-as "
COMP = "./" + TOOL_PATH + TOOL_NAME + "-gcc "

from sys import argv
from os import makedirs
from subprocess import run as subRun

modules = ["core", "libc", "tty"]

makedirs("bin/", exist_ok=True)
clean = "clean" in argv

def run(cmd: str) -> None: 
    print("[+]:", cmd)
    subRun(cmd, shell=True)

if "core" in argv or clean:
    run(AS + "src/kernel/boot.S -nostdlib -o bin/boot.o")
    run(COMP + "-c src/kernel/caesar.c -std=c2x -ffreestanding -nostdlib -o bin/core.o")
if "libc" in argv or clean:
    run(COMP + "-c src/libc/libc.c -std=c2x -ffreestanding -nostdlib -o bin/libc.o")
if "tty" in argv or clean:
    run(COMP + "-c src/kernel/tty.c -std=c2x -ffreestanding -nostdlib -o bin/tty.o")

modulesOuts = " ".join(["bin/" + x + ".o" for x in modules]) + " bin/boot.o"
run(COMP + "-T linker.ld -o bin/caesar.bin -ffreestanding -nostdlib " + modulesOuts)
