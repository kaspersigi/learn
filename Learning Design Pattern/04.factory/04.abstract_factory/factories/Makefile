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
all : ChicagoPizzaIngredientFactory.o NYPizzaIngredientFactory.o
ChicagoPizzaIngredientFactory.o : ChicagoPizzaIngredientFactory.cc ChicagoPizzaIngredientFactory.h
	$(CXX) ChicagoPizzaIngredientFactory.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
NYPizzaIngredientFactory.o : NYPizzaIngredientFactory.cc NYPizzaIngredientFactory.h
	$(CXX) NYPizzaIngredientFactory.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) ChicagoPizzaIngredientFactory.cc -style=file -i
	$(FORMAT) ChicagoPizzaIngredientFactory.h -style=file -i
	$(FORMAT) NYPizzaIngredientFactory.cc -style=file -i
	$(FORMAT) NYPizzaIngredientFactory.h -style=file -i
clean :
	rm -v ChicagoPizzaIngredientFactory.o
	rm -v NYPizzaIngredientFactory.o