###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : CoffeeWithHook.o TeaWithHook.o
CoffeeWithHook.o : CoffeeWithHook.cc CoffeeWithHook.h
	$(CXX) CoffeeWithHook.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
TeaWithHook.o : TeaWithHook.cc TeaWithHook.h
	$(CXX) TeaWithHook.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) CoffeeWithHook.cc -style=file -i
	$(FORMAT) CoffeeWithHook.h -style=file -i
	$(FORMAT) TeaWithHook.cc -style=file -i
	$(FORMAT) TeaWithHook.h -style=file -i
	$(FORMAT) beverages.h -style=file -i
clean :
	rm -v CoffeeWithHook.o TeaWithHook.o