#################################x86_64##########
#Makefile for my C programs
###########################################
TRG = all
EXEC = main
BIN = mbr.bin kernel.bin
OBJ = mbr.o kernel.o
SRC = mbr.s kernel.s
AS = /usr/bin/x86_64-linux-gnu-as
LD = /usr/bin/x86_64-linux-gnu-ld
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = x86_64-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=x86_64-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(BIN) boot.img
	dd if=mbr.bin of=boot.img count=1 bs=1440k conv=sync
	dd if=kernel.bin of=boot.img count=2880k bs=512 conv=notrunc seek=1
	rm -v $(BIN)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
mbr.bin : mbr.o
	$(LD) mbr.o -o mbr.bin -e _start -Ttext 0x7C00 --oformat binary -m elf_x86_64
	rm -v mbr.o
mbr.o : mbr.s
	$(CC) mbr.s -c
kernel.bin : kernel.o
	$(LD) kernel.o -o kernel.bin -e _start -Ttext 0x0000 --oformat binary -m elf_x86_64
	rm -v kernel.o
kernel.o : kernel.s
	$(CC) kernel.s -c
clean :
	rm -v boot.img
qemu :
	qemu-system-x86_64 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 2M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc