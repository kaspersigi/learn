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
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
all : DinerMenu.o PancakeHouseMenu.o
DinerMenu.o : DinerMenu.cc DinerMenu.h
	$(CXX) DinerMenu.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
PancakeHouseMenu.o : PancakeHouseMenu.cc PancakeHouseMenu.h
	$(CXX) PancakeHouseMenu.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) DinerMenu.cc -style=file -i
	$(FORMAT) DinerMenu.h -style=file -i
	$(FORMAT) PancakeHouseMenu.cc -style=file -i
	$(FORMAT) PancakeHouseMenu.h -style=file -i
	$(FORMAT) menus.h -style=file -i
clean :
	rm -v DinerMenu.o PancakeHouseMenu.o