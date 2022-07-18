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
RELEASE = -static -O3
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : Pizza
Pizza : Pizza.o interface.o factory.o pizzas.o store.o
	$(CXX) Pizza.o interface/Pizza.o factory/SimplePizzaFactory.o pizzas/CheesePizza.o pizzas/ClamPizza.o pizzas/PepperoniPizza.o pizzas/VeggiePizza.o store/PizzaStore.o -o Pizza $(CLANGXX_LINK_FLAGS)
	rm -v Pizza.o
	cd interface && make clean
	cd factory && make clean
	cd pizzas && make clean
	cd store && make clean
Pizza.o : Pizza.cc Pizza.h
	$(CXX) Pizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	cd interface && make
factory.o :
	cd factory && make
pizzas.o :
	cd pizzas && make
store.o :
	cd store && make
format :
	$(FORMAT) Pizza.cc -style=file -i
	$(FORMAT) Pizza.h -style=file -i
	cd interface && make format
	cd factory && make format
	cd pizzas && make format
	cd store && make format
clean :
	rm -v Pizza