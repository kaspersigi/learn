###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
CC = /usr/bin/clang
CXX = /usr/bin/clang++
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
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