###########################################
#Makefile for my C programs
###########################################
TRG = all
EXEC = main
BIN = main.bin
OBJ = main.o
SRC = main.s
AS = /usr/bin/i686-linux-gnu-as
LD = /usr/bin/i686-linux-gnu-ld
LLVM = -20
CONFIG = llvm-config$(LLVM)
ARCH = i686-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM)
CXX = /usr/bin/clang++$(LLVM)
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
	./util main.bin
	dd if=main.bin of=boot.img count=1 bs=1440k conv=sync
	rm -v $(OBJ) func.o $(BIN) util
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
$(BIN) : main.o func.o util
	$(LD) $(OBJ) func.o -o $(BIN) -N -e _start -Ttext 0x7C00 --oformat binary -m elf_i386
util : util.o
	$(CC) util.o -o util
	rm -v util.o
util.o : util.c
	$(CC) util.c -c $(C_FLAGS) $(DEBUG)
main.o :
	# $(AS) $(SRC) -o $(OBJ) --32
	$(CC) --target=i686-unknown-linux-gnu $(SRC) -c
func.o : func.c
	$(CC) --target=i686-unknown-linux-gnu func.c -c $(C_FLAGS) $(RELEASE)
clean :
	rm -v boot.img
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 1M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc