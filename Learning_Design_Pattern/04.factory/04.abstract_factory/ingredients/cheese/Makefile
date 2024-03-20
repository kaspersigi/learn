###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = 17
CONFIG = llvm-config-$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang-$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++-$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format-$(LLVM)
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : MozzarellaCheese.o ParmesanCheese.o ReggianoCheese.o
MozzarellaCheese.o : MozzarellaCheese.cc MozzarellaCheese.h
	$(CXX) MozzarellaCheese.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ParmesanCheese.o : ParmesanCheese.cc ParmesanCheese.h
	$(CXX) ParmesanCheese.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ReggianoCheese.o : ReggianoCheese.cc ReggianoCheese.h
	$(CXX) ReggianoCheese.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) MozzarellaCheese.cc -style=file -i
	$(FORMAT) MozzarellaCheese.h -style=file -i
	$(FORMAT) ParmesanCheese.cc -style=file -i
	$(FORMAT) ParmesanCheese.h -style=file -i
	$(FORMAT) ReggianoCheese.cc -style=file -i
	$(FORMAT) ReggianoCheese.h -style=file -i
clean :
	rm -v MozzarellaCheese.o ParmesanCheese.o ReggianoCheese.o