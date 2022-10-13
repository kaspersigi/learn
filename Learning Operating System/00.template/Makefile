###########################################
#Makefile for my C programs
###########################################
TRG = all
EXEC = main
BIN = main.bin
OBJ = main.o
SRC = main.s
AS = /usr/bin/as
LD = /usr/bin/ld
CC = /usr/bin/clang
CXX = /usr/bin/clang++
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(BIN) boot.img
	dd if=main.bin of=boot.img count=1 bs=1440k conv=sync
	rm -v $(BIN)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
$(BIN) : $(OBJ)
	$(LD) $(OBJ) -o $(BIN) -e _start -Ttext 0x7C00 --oformat binary -m elf_i386
	rm -v $(OBJ)
$(OBJ) : main.s
	$(AS) $(SRC) -o $(OBJ) --32
clean :
	rm -v boot.img
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 1M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc