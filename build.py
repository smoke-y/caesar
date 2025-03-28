TOOL_NAME = "i686-elf"
TOOL_PATH = "tools/" + TOOL_NAME + "/bin/"

AS   = "./" + TOOL_PATH + TOOL_NAME + "-as "
COMP = "./" + TOOL_PATH + TOOL_NAME + "-gcc "

from sys import argv
from os import makedirs
from subprocess import run as subRun

modules = ["core"]

makedirs("bin/", exist_ok=True)
scratch = "scratch" in argv

def run(cmd: str) -> None: 
    print("[+]:", cmd)
    subRun(cmd, shell=True)

if "core" in argv or scratch:
    run(AS + "src/kernel/boot.S -o bin/boot.o")
    run(COMP + "-c src/kernel/core.c -std=c2x -ffreestanding -o bin/core.o")

modulesOuts = " ".join(["bin/" + x + ".o" for x in modules]) + " bin/boot.o"
run(COMP + "-T linker.ld -o bin/caesar.bin -ffreestanding -nostdlib " + modulesOuts)
