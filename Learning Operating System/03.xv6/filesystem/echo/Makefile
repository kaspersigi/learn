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
all : _echo
_echo : ulib.o printf.o umalloc.o echo.o usys.o
	$(LD) ulib.o printf.o umalloc.o echo.o usys.o -o _echo -N -e main -Ttext 0x0 -m elf_i386
	rm -v ulib.o printf.o umalloc.o echo.o usys.o
ulib.o : ulib.c
	$(CC) ulib.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
printf.o : printf.c
	$(CC) printf.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
umalloc.o : umalloc.c
	$(CC) umalloc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
echo.o : echo.c
	$(CC) echo.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
usys.o : usys.S
	$(CC) usys.S -c -gdwarf-2 -Wa,-divide $(ARCH)
format :
	$(FORMAT) ulib.c -style=file -i
	$(FORMAT) printf.c -style=file -i
	$(FORMAT) umalloc.c -style=file -i
	$(FORMAT) echo.c -style=file -i
clean :
	rm -v _echo