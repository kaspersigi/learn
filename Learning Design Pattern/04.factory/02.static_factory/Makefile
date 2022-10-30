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
all : Pizza
Pizza : Pizza.o interface.o factory.o pizzas.o store.o
	$(CXX) Pizza.o interface/*.o factory/*.o pizzas/*.o store/*.o -o Pizza $(CLANGXX_LINK_FLAGS)
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