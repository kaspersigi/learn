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
all : DinerMerger
DinerMerger : DinerMerger.o interface.o iterators.o menus.o waitress.o
	$(CXX) DinerMerger.o interface/*.o iterators/*.o menus/*.o waitress/*.o -o DinerMerger $(CLANGXX_LINK_FLAGS)
	rm -v DinerMerger.o
	$(MAKE) -C interface clean
	$(MAKE) -C iterators clean
	$(MAKE) -C menus clean
	$(MAKE) -C waitress clean
DinerMerger.o : DinerMerger.cc DinerMerger.h
	$(CXX) DinerMerger.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
iterators.o :
	$(MAKE) -C iterators
menus.o :
	$(MAKE) -C menus
waitress.o :
	$(MAKE) -C waitress
format :
	$(FORMAT) DinerMerger.cc -style=file -i
	$(FORMAT) DinerMerger.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C iterators format
	$(MAKE) -C menus format
	$(MAKE) -C waitress format
clean :
	rm -v DinerMerger
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./DinerMerger