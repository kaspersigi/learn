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
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : DuckSimulator
DuckSimulator : DuckSimulator.o interface.o ducks.o flyBehaviors.o quackBehaviors.o
	$(CXX) DuckSimulator.o interface/*.o ducks/*.o flyBehaviors/*.o quackBehaviors/*.o -o DuckSimulator $(CLANGXX_LINK_FLAGS)
	rm -v DuckSimulator.o
	$(MAKE) -C interface clean
	$(MAKE) -C ducks clean
	$(MAKE) -C flyBehaviors clean
	$(MAKE) -C quackBehaviors clean
DuckSimulator.o : DuckSimulator.cc DuckSimulator.h
	$(CXX) DuckSimulator.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
ducks.o :
	$(MAKE) -C ducks
flyBehaviors.o :
	$(MAKE) -C flyBehaviors
quackBehaviors.o :
	$(MAKE) -C quackBehaviors
format :
	$(FORMAT) DuckSimulator.cc -style=file -i
	$(FORMAT) DuckSimulator.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C ducks format
	$(MAKE) -C flyBehaviors format
	$(MAKE) -C quackBehaviors format
clean :
	rm -v DuckSimulator
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./DuckSimulator