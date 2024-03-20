###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = -17
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : DuckAdapter.o TurkeyAdapter.o
DuckAdapter.o : DuckAdapter.cc DuckAdapter.h
	$(CXX) DuckAdapter.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
TurkeyAdapter.o : TurkeyAdapter.cc TurkeyAdapter.h
	$(CXX) TurkeyAdapter.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) DuckAdapter.cc -style=file -i
	$(FORMAT) DuckAdapter.h -style=file -i
	$(FORMAT) TurkeyAdapter.cc -style=file -i
	$(FORMAT) TurkeyAdapter.h -style=file -i
clean :
	rm -v DuckAdapter.o TurkeyAdapter.o