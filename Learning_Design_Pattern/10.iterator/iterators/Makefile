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
all : DinerMenuIterator.o PancakeHouseMenuIterator.o
DinerMenuIterator.o : DinerMenuIterator.cc DinerMenuIterator.h
	$(CXX) DinerMenuIterator.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
PancakeHouseMenuIterator.o : PancakeHouseMenuIterator.cc PancakeHouseMenuIterator.h
	$(CXX) PancakeHouseMenuIterator.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) DinerMenuIterator.cc -style=file -i
	$(FORMAT) DinerMenuIterator.h -style=file -i
	$(FORMAT) PancakeHouseMenuIterator.cc -style=file -i
	$(FORMAT) PancakeHouseMenuIterator.h -style=file -i
	$(FORMAT) iterators.h -style=file -i
clean :
	rm -v DinerMenuIterator.o PancakeHouseMenuIterator.o