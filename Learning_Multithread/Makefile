###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = -20
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
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
all : template atomic mutex condition_variable detach async
template :
	$(MAKE) -C 00.template
atomic :
	$(MAKE) -C 01.atomic
mutex :
	$(MAKE) -C 02.mutex
condition_variable :
	$(MAKE) -C 03.condition_variable
detach :
	$(MAKE) -C 04.detach
async :
	$(MAKE) -C 05.async

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.atomic format
	$(MAKE) -C 02.mutex format
	$(MAKE) -C 03.condition_variable format
	$(MAKE) -C 04.detach format
	$(MAKE) -C 05.async format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.atomic clean
	$(MAKE) -C 02.mutex clean
	$(MAKE) -C 03.condition_variable clean
	$(MAKE) -C 04.detach clean
	$(MAKE) -C 05.async clean