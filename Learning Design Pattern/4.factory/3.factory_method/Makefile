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
all : Pizzafm
Pizzafm : Pizzafm.o interface.o factories.o pizzas.o
	$(CXX) Pizzafm.o interface/Pizza.o interface/PizzaStore.o factories/ChicagoPizzaStore.o factories/NYPizzaStore.o pizzas/ChicagoStyleCheesePizza.o pizzas/ChicagoStyleClamPizza.o pizzas/ChicagoStylePepperoniPizza.o pizzas/ChicagoStyleVeggiePizza.o pizzas/NYStyleCheesePizza.o pizzas/NYStyleClamPizza.o pizzas/NYStylePepperoniPizza.o pizzas/NYStyleVeggiePizza.o -o Pizzafm $(CLANGXX_LINK_FLAGS)
	rm -v Pizzafm.o
	cd interface && make clean
	cd factories && make clean
	cd pizzas && make clean
Pizzafm.o : Pizzafm.cc Pizzafm.h
	$(CXX) Pizzafm.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	cd interface && make
factories.o :
	cd factories && make
pizzas.o :
	cd pizzas && make
format :
	$(FORMAT) Pizzafm.cc -style=file -i
	$(FORMAT) Pizzafm.h -style=file -i
	cd interface && make format
	cd factories && make format
	cd pizzas && make format
clean :
	rm -v Pizzafm