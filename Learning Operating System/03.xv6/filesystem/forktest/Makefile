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
CC = /usr/bin/gcc
CXX = /usr/bin/g++
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -O3
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
ARCH = -m32
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -no-pie -static

.PHONY : all
all : _forktest
_forktest : ulib.o forktest.o usys.o
	$(LD) ulib.o forktest.o usys.o -o _forktest -N -e main -Ttext 0x0 -m elf_i386
	rm -v ulib.o forktest.o usys.o
ulib.o : ulib.c
	$(CC) ulib.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
forktest.o : forktest.c
	$(CC) forktest.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
usys.o : usys.S
	$(CC) usys.S -c -gdwarf-2 -Wa,-divide $(ARCH)
format :
	$(FORMAT) ulib.c -style=file -i
	$(FORMAT) forktest.c -style=file -i
clean :
	rm -v _forktest