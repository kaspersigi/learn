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
all : FlyNoWay.o FlyRocketPowered.o FlyWithWings.o
FlyNoWay.o : FlyNoWay.cc FlyNoWay.h
	$(CXX) FlyNoWay.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
FlyRocketPowered.o : FlyRocketPowered.cc FlyRocketPowered.h
	$(CXX) FlyRocketPowered.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
FlyWithWings.o : FlyWithWings.cc FlyWithWings.h
	$(CXX) FlyWithWings.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) flyBehaviors.h -style=file -i
	$(FORMAT) FlyNoWay.cc -style=file -i
	$(FORMAT) FlyNoWay.h -style=file -i
	$(FORMAT) FlyRocketPowered.cc -style=file -i
	$(FORMAT) FlyRocketPowered.h -style=file -i
	$(FORMAT) FlyWithWings.cc -style=file -i
	$(FORMAT) FlyWithWings.h -style=file -i
clean :
	rm -v FlyNoWay.o
	rm -v FlyRocketPowered.o
	rm -v FlyWithWings.o