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
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -static

.PHONY : all
all : mkfs _common _cat _echo _forktest
	./mkfs fs.img README _cat _echo _forktest
	$(MAKE) -C common clean
	rm -v mkfs _cat _echo _forktest
mkfs : mkfs.o
	$(CC) mkfs.o -o mkfs
	rm -v mkfs.o
mkfs.o : mkfs.c
	$(CC) mkfs.c -c $(C_FLAGS) $(DEBUG)
_common : common
	$(MAKE) -C common
_cat : cat.c
	$(CC) cat.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
	$(LD) cat.o common/ulib.o common/printf.o common/umalloc.o common/usys.o -o _cat -N -e main -Ttext 0x0 -m elf_i386
	rm -v cat.o
_echo : echo.c
	$(CC) echo.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
	$(LD) echo.o common/ulib.o common/printf.o common/umalloc.o common/usys.o -o _echo -N -e main -Ttext 0x0 -m elf_i386
	rm -v echo.o
_forktest : forktest.c
	$(CC) forktest.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
	$(LD) forktest.o common/ulib.o common/usys.o -o _forktest -N -e main -Ttext 0x0 -m elf_i386
	rm -v forktest.o
format :
	$(FORMAT) mkfs.c -style=file -i
	$(MAKE) -C common format
	$(FORMAT) cat.c -style=file -i
	$(FORMAT) echo.c -style=file -i
	$(FORMAT) forktest.c -style=file -i
clean :
	rm -v fs.img