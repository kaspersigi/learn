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
all : Starbuzz
Starbuzz : Starbuzz.o interface.o components.o decorators.o
	$(CXX) Starbuzz.o ./interface/Beverage.o ./components/DarkRoast.o ./components/Decaf.o ./components/Espresso.o ./components/HouseBlend.o ./decorators/Milk.o ./decorators/Mocha.o ./decorators/Soy.o ./decorators/Whip.o -o Starbuzz $(CLANGXX_LINK_FLAGS)
	rm -v Starbuzz.o
	cd interface && make clean
	cd components && make clean
	cd decorators && make clean
Starbuzz.o : Starbuzz.cc Starbuzz.h
	$(CXX) Starbuzz.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	cd interface && make
components.o :
	cd components && make
decorators.o :
	cd decorators && make
format :
	$(FORMAT) Starbuzz.cc -style=file -i
	$(FORMAT) Starbuzz.h -style=file -i
	cd interface && make format
	cd components && make format
	cd decorators && make format
clean :
	rm -v Starbuzz