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
all : Chocolate
Chocolate : Chocolate.o singleton.o
	$(CXX) Chocolate.o singleton/*.o -o Chocolate $(CLANGXX_LINK_FLAGS)
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