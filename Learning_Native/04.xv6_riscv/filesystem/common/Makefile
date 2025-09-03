###########################################
#Makefile for my C programs
###########################################
TRG = all
EXEC = main
BIN = main.bin
OBJ = main.o
SRC = main.s
AS = /usr/bin/riscv64-linux-gnu-as
LD = /usr/bin/riscv64-linux-gnu-ld
OBJCOPY = /usr/bin/riscv64-linux-gnu-objcopy
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = i686-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=riscv64-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -Oz
LINK_FLAGS = -z max-page-size=4096
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-omit-frame-pointer -ffreestanding -fno-common -fno-pic -fno-pie -static -mno-relax -mcmodel=medany

.PHONY : all
all : printf.o ulib.o umalloc.o usys.o
printf.o : printf.c
	$(CC) printf.c -c $(C_FLAGS) -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -static -mcmodel=medany $(DEBUG)
ulib.o : ulib.c
	$(CC) ulib.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
umalloc.o : umalloc.c
	$(CC) umalloc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
usys.o : usys.S
	$(CC) usys.S -c -gdwarf-2 -g
	rm -v usys.S
usys.S : usys.pl
	perl usys.pl > usys.S
format :
	$(FORMAT) printf.c -style=file -i
	$(FORMAT) ulib.c -style=file -i
	$(FORMAT) umalloc.c -style=file -i
clean :
	rm -v printf.o ulib.o umalloc.o usys.o