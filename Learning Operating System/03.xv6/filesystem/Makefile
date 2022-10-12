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
all : mkfs _cat _echo _forktest
	mv cat/_cat .
	mv echo/_echo .
	mv forktest/_forktest .
	./mkfs fs.img README _cat _echo _forktest
	rm -v mkfs _cat _echo _forktest
mkfs : mkfs.o
	$(CC) mkfs.o -o mkfs
	rm -v mkfs.o
mkfs.o : mkfs.c
	$(CC) mkfs.c -c $(C_FLAGS) $(DEBUG)
_cat : cat
	$(MAKE) -C cat
_echo : echo
	$(MAKE) -C echo
_forktest : cat
	$(MAKE) -C forktest
format :
	$(FORMAT) mkfs.c -style=file -i
	$(MAKE) -C cat format
	$(MAKE) -C echo format
	$(MAKE) -C forktest format
clean :
	rm -v fs.img