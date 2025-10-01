###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_Driver
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -flto -O3
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
all : template module module_param export_symbol char
template :
	$(MAKE) -C 00.template
module :
	$(MAKE) -C 01.module
module_param :
	$(MAKE) -C 02.module_param
export_symbol :
	$(MAKE) -C 03.export_symbol
char :
	$(MAKE) -C 04.char

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.module format
	$(MAKE) -C 02.module_param format
	$(MAKE) -C 03.export_symbol format
	$(MAKE) -C 04.char format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.module clean
	$(MAKE) -C 02.module_param clean
	$(MAKE) -C 03.export_symbol clean
	$(MAKE) -C 04.char clean

scan :
	$(MAKE) -C 00.template scan
	$(MAKE) -C 01.module scan
	$(MAKE) -C 02.module_param scan
	$(MAKE) -C 03.export_symbol scan
	$(MAKE) -C 04.char scan