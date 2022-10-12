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
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -static

.PHONY : all
all : entryother
entryother : bootblockother.o
	objcopy bootblockother.o -S -O binary -j .text entryother
	rm -v bootblockother.o
bootblockother.o : entryother.o
	$(LD) entryother.o -o bootblockother.o -N -e start -Ttext 0x7000 -m elf_i386
	rm -v entryother.o
entryother.o : entryother.S
	$(CC) entryother.S -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
clean :
	rm -v entryother