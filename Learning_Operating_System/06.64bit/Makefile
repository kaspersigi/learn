###########################################
#Makefile for my C programs
###########################################
TRG = all
EXEC = main
BIN = main.bin
OBJ = main.o
SRC = main.s
AS = /usr/bin/x86_64-linux-gnu-as
LD = /usr/bin/x86_64-linux-gnu-ld
LLVM = -20
CONFIG = llvm-config$(LLVM)
ARCH = x86_64-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=x86_64-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -O3
LIBS = -lpthread
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(BIN) boot.img
	dd if=main.bin of=boot.img count=1 bs=1440k conv=sync
	rm -v $(BIN)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
$(BIN) : $(OBJ)
	$(LD) $(OBJ) -o $(BIN) -e _start -Ttext 0x7C00 --oformat binary -m elf_x86_64
	rm -v $(OBJ)
$(OBJ) : main.s
	$(CC) $(SRC) -c
clean :
	rm -v boot.img
qemu :
	qemu-system-x86_64 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 2M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc