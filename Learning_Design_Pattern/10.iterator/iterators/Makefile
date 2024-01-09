###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
ARCH = $(shell llvm-config --host-target)
CC = /usr/bin/clang --target=$(ARCH)
CXX = /usr/bin/clang++ --target=$(ARCH)
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c2x -Wall -Wno-unused
CXX_FLAGS = -std=c++2b -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

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