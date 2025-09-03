###########################################
#Makefile for my assembler programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_Operating_System
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -O3
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
all : template protected function_call paging pae ia32e 64bit long_mode gdt rip stack kernel idt star
template :
	$(MAKE) -C 00.template
protected :
	$(MAKE) -C 01.protected
function_call :
	$(MAKE) -C 02.function_call
paging :
	$(MAKE) -C 03.paging
pae :
	$(MAKE) -C 04.pae
ia32e :
	$(MAKE) -C 05.ia32e
64bit :
	$(MAKE) -C 06.64bit
long_mode :
	$(MAKE) -C 07.long_mode
gdt :
	$(MAKE) -C 08.gdt
rip :
	$(MAKE) -C 09.rip
stack :
	$(MAKE) -C 10.stack
kernel :
	$(MAKE) -C 11.kernel
idt :
	$(MAKE) -C 12.idt
star :
	$(MAKE) -C 13.star

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.protected clean
	$(MAKE) -C 02.function_call clean
	$(MAKE) -C 03.paging clean
	$(MAKE) -C 04.pae clean
	$(MAKE) -C 05.ia32e clean
	$(MAKE) -C 06.64bit clean
	$(MAKE) -C 07.long_mode clean
	$(MAKE) -C 08.gdt clean
	$(MAKE) -C 09.rip clean
	$(MAKE) -C 10.stack clean
	$(MAKE) -C 11.kernel clean
	$(MAKE) -C 12.idt clean
	$(MAKE) -C 13.star clean