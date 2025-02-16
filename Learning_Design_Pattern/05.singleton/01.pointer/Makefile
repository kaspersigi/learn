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
all : Chocolate
Chocolate : Chocolate.o singleton.o
	$(CXX) Chocolate.o singleton/*.o -o Chocolate $(CLANGXX_LINK_FLAGS) $(DEBUG)
	rm -v Chocolate.o
	$(MAKE) -C singleton clean
Chocolate.o : Chocolate.cc Chocolate.h
	$(CXX) Chocolate.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
singleton.o :
	$(MAKE) -C singleton
format :
	$(FORMAT) Chocolate.cc -style=file -i
	$(FORMAT) Chocolate.h -style=file -i
	$(MAKE) -C singleton format
clean :
	rm -v Chocolate
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./Chocolate