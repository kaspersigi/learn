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
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = i686-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=i686-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=i686-unknown-linux-gnu
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
TIDY = /usr/bin/clang-tidy$(LLVM)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -Oz
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -static
TIDY_FLAGS = -- --target=i686-unknown-linux-gnu $(C_FLAGS) $(DEBUG)

.PHONY : all
all : ulib.o printf.o umalloc.o usys.o
ulib.o : ulib.c
	$(CC) ulib.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
printf.o : printf.c
	$(CC) printf.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
umalloc.o : umalloc.c
	$(CC) umalloc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
usys.o : usys.S
	$(CC) usys.S -c -gdwarf-2 -g
format :
	$(FORMAT) ulib.c -style=file -i
	$(FORMAT) printf.c -style=file -i
	$(FORMAT) umalloc.c -style=file -i
clean :
	rm -v ulib.o printf.o umalloc.o usys.o