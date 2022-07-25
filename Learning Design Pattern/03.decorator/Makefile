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
	$(MAKE) -C interface clean
	$(MAKE) -C components clean
	$(MAKE) -C decorators clean
Starbuzz.o : Starbuzz.cc Starbuzz.h
	$(CXX) Starbuzz.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
components.o :
	$(MAKE) -C components
decorators.o :
	$(MAKE) -C decorators
format :
	$(FORMAT) Starbuzz.cc -style=file -i
	$(FORMAT) Starbuzz.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C components format
	$(MAKE) -C decorators format
clean :
	rm -v Starbuzz