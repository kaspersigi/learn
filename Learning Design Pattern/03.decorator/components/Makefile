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
all : DarkRoast.o Decaf.o Espresso.o HouseBlend.o
DarkRoast.o : DarkRoast.cc DarkRoast.h
	$(CXX) DarkRoast.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Decaf.o : Decaf.cc Decaf.h
	$(CXX) Decaf.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Espresso.o : Espresso.cc Espresso.h
	$(CXX) Espresso.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
HouseBlend.o : HouseBlend.cc HouseBlend.h
	$(CXX) HouseBlend.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) components.h -style=file -i
	$(FORMAT) DarkRoast.cc -style=file -i
	$(FORMAT) DarkRoast.h -style=file -i
	$(FORMAT) Decaf.cc -style=file -i
	$(FORMAT) Decaf.h -style=file -i
	$(FORMAT) Espresso.cc -style=file -i
	$(FORMAT) Espresso.h -style=file -i
	$(FORMAT) HouseBlend.cc -style=file -i
	$(FORMAT) HouseBlend.h -style=file -i
clean :
	rm -v DarkRoast.o
	rm -v Decaf.o
	rm -v Espresso.o
	rm -v HouseBlend.o