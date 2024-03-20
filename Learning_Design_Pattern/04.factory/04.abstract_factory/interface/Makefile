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
all : Pizza.o PizzaStore.o
Pizza.o : Pizza.cc Pizza.h
	$(CXX) Pizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
PizzaStore.o : PizzaStore.cc PizzaStore.h
	$(CXX) PizzaStore.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) Pizza.cc -style=file -i
	$(FORMAT) Pizza.h -style=file -i
	$(FORMAT) PizzaStore.cc -style=file -i
	$(FORMAT) PizzaStore.h -style=file -i
	$(FORMAT) Cheese.h -style=file -i
	$(FORMAT) Clams.h -style=file -i
	$(FORMAT) Dough.h -style=file -i
	$(FORMAT) Pepperoni.h -style=file -i
	$(FORMAT) Sauce.h -style=file -i
	$(FORMAT) Veggies.h -style=file -i
	$(FORMAT) PizzaIngredientFactory.h -style=file -i
clean :
	rm -v Pizza.o PizzaStore.o