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
ARCH = i386-unknown-linux-gnu
CC = /usr/bin/clang --target=i386-unknown-linux-gnu
CXX = /usr/bin/clang++ --target=$(ARCH)
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -static

.PHONY : all
all : ulib.o printf.o umalloc.o usys.o
ulib.o : ulib.c
	$(CC) ulib.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
printf.o : printf.c
	$(CC) printf.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
umalloc.o : umalloc.c
	$(CC) umalloc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
usys.o : usys.S
	$(CC) usys.S -c -gdwarf-2
format :
	$(FORMAT) ulib.c -style=file -i
	$(FORMAT) printf.c -style=file -i
	$(FORMAT) umalloc.c -style=file -i
clean :
	rm -v ulib.o printf.o umalloc.o usys.o