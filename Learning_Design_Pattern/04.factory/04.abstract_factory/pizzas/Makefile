###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : CheesePizza.o ClamPizza.o PepperoniPizza.o VeggiePizza.o
CheesePizza.o : CheesePizza.cc CheesePizza.h
	$(CXX) CheesePizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ClamPizza.o : ClamPizza.cc ClamPizza.h
	$(CXX) ClamPizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
PepperoniPizza.o : PepperoniPizza.cc PepperoniPizza.h
	$(CXX) PepperoniPizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
VeggiePizza.o : VeggiePizza.cc VeggiePizza.h
	$(CXX) VeggiePizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) CheesePizza.cc -style=file -i
	$(FORMAT) CheesePizza.h -style=file -i
	$(FORMAT) ClamPizza.cc -style=file -i
	$(FORMAT) ClamPizza.h -style=file -i
	$(FORMAT) PepperoniPizza.cc -style=file -i
	$(FORMAT) PepperoniPizza.h -style=file -i
	$(FORMAT) VeggiePizza.cc -style=file -i
	$(FORMAT) VeggiePizza.h -style=file -i
	$(FORMAT) pizzas.h -style=file -i
clean :
	rm -v CheesePizza.o ClamPizza.o PepperoniPizza.o VeggiePizza.o