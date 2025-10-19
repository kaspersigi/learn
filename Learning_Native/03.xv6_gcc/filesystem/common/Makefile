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
CC = /usr/bin/i686-linux-gnu-gcc
CXX = /usr/bin/g++
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/i686-linux-gnu-gcc
TIDY = /usr/bin/clang-tidy$(LLVM)
LLVM = -21
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c2x -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -O2
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++
ARCH = -m32
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -static
TIDY_FLAGS = -- --target=i686-unknown-linux-gnu $(C_FLAGS) $(DEBUG)

.PHONY : all
all : ulib.o printf.o umalloc.o usys.o
ulib.o : ulib.c
	$(CC) ulib.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
printf.o : printf.c
	$(CC) printf.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
umalloc.o : umalloc.c
	$(CC) umalloc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
usys.o : usys.S
	$(CC) usys.S -c -gdwarf-2 -Wa,-divide $(ARCH) -g
format :
	$(FORMAT) ulib.c -style=file -i
	$(FORMAT) printf.c -style=file -i
	$(FORMAT) umalloc.c -style=file -i
clean :
	rm -v ulib.o printf.o umalloc.o usys.o