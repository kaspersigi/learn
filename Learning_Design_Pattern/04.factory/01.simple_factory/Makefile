###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = -19
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
all : Pizza
Pizza : Pizza.o interface.o factory.o pizzas.o store.o
	$(CXX) Pizza.o interface/*.o factory/*.o pizzas/*.o store/*.o -o Pizza $(CLANGXX_LINK_FLAGS) $(DEBUG)
	rm -v Pizza.o
	$(MAKE) -C interface clean
	$(MAKE) -C factory clean
	$(MAKE) -C pizzas clean
	$(MAKE) -C store clean
Pizza.o : Pizza.cc Pizza.h
	$(CXX) Pizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
factory.o :
	$(MAKE) -C factory
pizzas.o :
	$(MAKE) -C pizzas
store.o :
	$(MAKE) -C store
format :
	$(FORMAT) Pizza.cc -style=file -i
	$(FORMAT) Pizza.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C factory format
	$(MAKE) -C pizzas format
	$(MAKE) -C store format
clean :
	rm -v Pizza
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./Pizza