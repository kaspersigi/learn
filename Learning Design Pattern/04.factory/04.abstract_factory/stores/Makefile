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
all : ChicagoPizzaStore.o NYPizzaStore.o
ChicagoPizzaStore.o : ChicagoPizzaStore.cc ChicagoPizzaStore.h
	$(CXX) ChicagoPizzaStore.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
NYPizzaStore.o : NYPizzaStore.cc NYPizzaStore.h
	$(CXX) NYPizzaStore.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) ChicagoPizzaStore.cc -style=file -i
	$(FORMAT) ChicagoPizzaStore.h -style=file -i
	$(FORMAT) NYPizzaStore.cc -style=file -i
	$(FORMAT) NYPizzaStore.h -style=file -i
	$(FORMAT) stores.h -style=file -i
clean :
	rm -v ChicagoPizzaStore.o
	rm -v NYPizzaStore.o