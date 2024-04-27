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
all : Pizzafm
Pizzafm : Pizzafm.o interface.o factories.o pizzas.o
	$(CXX) Pizzafm.o interface/*.o factories/*.o pizzas/*.o -o Pizzafm $(CLANGXX_LINK_FLAGS)
	rm -v Pizzafm.o
	$(MAKE) -C interface clean
	$(MAKE) -C factories clean
	$(MAKE) -C pizzas clean
Pizzafm.o : Pizzafm.cc Pizzafm.h
	$(CXX) Pizzafm.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
factories.o :
	$(MAKE) -C factories
pizzas.o :
	$(MAKE) -C pizzas
format :
	$(FORMAT) Pizzafm.cc -style=file -i
	$(FORMAT) Pizzafm.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C factories format
	$(MAKE) -C pizzas format
clean :
	rm -v Pizzafm
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./Pizzafm