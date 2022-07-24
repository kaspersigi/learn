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
all : Milk.o Mocha.o Soy.o Whip.o
Milk.o : Milk.cc Milk.h
	$(CXX) Milk.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Mocha.o : Mocha.cc Mocha.h
	$(CXX) Mocha.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Soy.o : Soy.cc Soy.h
	$(CXX) Soy.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Whip.o : Whip.cc Whip.h
	$(CXX) Whip.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) decorators.h -style=file -i
	$(FORMAT) Milk.cc -style=file -i
	$(FORMAT) Milk.h -style=file -i
	$(FORMAT) Mocha.cc -style=file -i
	$(FORMAT) Mocha.h -style=file -i
	$(FORMAT) Soy.cc -style=file -i
	$(FORMAT) Soy.h -style=file -i
	$(FORMAT) Whip.cc -style=file -i
	$(FORMAT) Whip.h -style=file -i
clean :
	rm -v Milk.o
	rm -v Mocha.o
	rm -v Soy.o
	rm -v Whip.o