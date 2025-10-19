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
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
TIDY = /usr/bin/clang-tidy$(LLVM)
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
TIDY_FLAGS = -- --target=$(ARCH) $(C_FLAGS) $(DEBUG)

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

scan :
	$(MAKE) -C 00.template scan
	$(MAKE) -C 01.protected scan
	$(MAKE) -C 02.function_call scan
	$(MAKE) -C 03.paging scan
	$(MAKE) -C 04.pae scan
	$(MAKE) -C 05.ia32e scan
	$(MAKE) -C 06.64bit scan
	$(MAKE) -C 07.long_mode scan
	$(MAKE) -C 08.gdt scan
	$(MAKE) -C 09.rip scan
	$(MAKE) -C 10.stack scan
	$(MAKE) -C 11.kernel scan
	$(MAKE) -C 12.idt scan
	$(MAKE) -C 13.star scan

tidy :
	$(MAKE) -C 00.template tidy
	$(MAKE) -C 01.protected tidy
	$(MAKE) -C 02.function_call tidy
	$(MAKE) -C 03.paging tidy
	$(MAKE) -C 04.pae tidy
	$(MAKE) -C 05.ia32e tidy
	$(MAKE) -C 06.64bit tidy
	$(MAKE) -C 07.long_mode tidy
	$(MAKE) -C 08.gdt tidy
	$(MAKE) -C 09.rip tidy
	$(MAKE) -C 10.stack tidy
	$(MAKE) -C 11.kernel tidy
	$(MAKE) -C 12.idt tidy
	$(MAKE) -C 13.star tidy