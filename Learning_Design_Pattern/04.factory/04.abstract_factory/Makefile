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
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : Pizzaaf
Pizzaaf : Pizzaaf.o interface.o ingredients.o factories.o pizzas.o stores.o
	$(CXX) Pizzaaf.o interface/*.o ingredients/cheese/*.o ingredients/clams/*.o ingredients/dough/*.o ingredients/pepperoni/*.o ingredients/sauce/*.o ingredients/veggies/*.o factories/*.o pizzas/*.o stores/*.o -o Pizzaaf $(CLANGXX_LINK_FLAGS)
	rm -v Pizzaaf.o
	$(MAKE) -C interface clean
	$(MAKE) -C ingredients clean
	$(MAKE) -C factories clean
	$(MAKE) -C pizzas clean
	$(MAKE) -C stores clean
Pizzaaf.o : Pizzaaf.cc Pizzaaf.h
	$(CXX) Pizzaaf.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
factories.o :
	$(MAKE) -C factories
ingredients.o :
	$(MAKE) -C ingredients
pizzas.o :
	$(MAKE) -C pizzas
stores.o :
	$(MAKE) -C stores
format :
	$(FORMAT) Pizzaaf.cc -style=file -i
	$(FORMAT) Pizzaaf.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C ingredients format
	$(MAKE) -C factories format
	$(MAKE) -C pizzas format
	$(MAKE) -C stores format
clean :
	rm -v Pizzaaf
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./Pizzaaf