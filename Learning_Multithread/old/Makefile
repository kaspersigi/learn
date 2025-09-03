###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
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
all : template Q1 Q2 Q3 Q4 Q5 Q6
template :
	$(MAKE) -C 00.template
Q1 :
	$(MAKE) -C 01.Q1
Q2 :
	$(MAKE) -C 02.Q2
Q3 :
	$(MAKE) -C 03.Q3
Q4 :
	$(MAKE) -C 04.Q4
Q5 :
	$(MAKE) -C 05.Q5
Q6 :
	$(MAKE) -C 06.Q6

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.Q1 format
	$(MAKE) -C 02.Q2 format
	$(MAKE) -C 03.Q3 format
	$(MAKE) -C 04.Q4 format
	$(MAKE) -C 05.Q5 format
	$(MAKE) -C 06.Q6 format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.Q1 clean
	$(MAKE) -C 02.Q2 clean
	$(MAKE) -C 03.Q3 clean
	$(MAKE) -C 04.Q4 clean
	$(MAKE) -C 05.Q5 clean
	$(MAKE) -C 06.Q6 clean