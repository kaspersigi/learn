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
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = i386-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=i386-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie

.PHONY : all
all : bootblock
bootblock : bootblock.o
	i686-linux-gnu-objcopy bootblock.o -S -O binary -j .text bootblock
	./sign.pl bootblock
bootblock.o : bootasm.o bootmain.o
	$(LD) bootasm.o bootmain.o -o bootblock.o -N -e start -Ttext 0x7C00 -m elf_i386
	rm -v bootasm.o bootmain.o
bootasm.o : bootasm.S
	$(CC) bootasm.S -c $(C_FLAGS) $(KERNEL_FLAGS) $(RELEASE)
bootmain.o : bootmain.c
	$(CC) bootmain.c -c $(C_FLAGS) $(KERNEL_FLAGS) -ggdb -Oz
format :
	$(FORMAT) bootmain.c -style=file -i
clean :
	rm -v bootblock.o