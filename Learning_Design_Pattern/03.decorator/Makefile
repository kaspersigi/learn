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
all : Starbuzz
Starbuzz : Starbuzz.o interface.o components.o decorators.o
	$(CXX) Starbuzz.o interface/*.o components/*.o decorators/*.o -o Starbuzz $(CLANGXX_LINK_FLAGS) $(DEBUG)
	rm -v Starbuzz.o
	$(MAKE) -C interface clean
	$(MAKE) -C components clean
	$(MAKE) -C decorators clean
Starbuzz.o : Starbuzz.cc Starbuzz.h
	$(CXX) Starbuzz.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
components.o :
	$(MAKE) -C components
decorators.o :
	$(MAKE) -C decorators
format :
	$(FORMAT) Starbuzz.cc -style=file -i
	$(FORMAT) Starbuzz.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C components format
	$(MAKE) -C decorators format
clean :
	rm -v Starbuzz
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./Starbuzz