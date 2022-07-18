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
all : DuckSimulator
DuckSimulator : DuckSimulator.o interface.o Ducks.o FlyBehaviors.o QuackBehaviors.o
	$(CXX) DuckSimulator.o ./interface/Duck.o ./ducks/DecoyDuck.o ./ducks/MallardDuck.o ./ducks/ModelDuck.o ./ducks/RedHeadDuck.o ./ducks/RubberDuck.o ./flyBehaviors/FlyNoWay.o ./flyBehaviors/FlyRocketPowered.o ./flyBehaviors/FlyWithWings.o ./quackBehaviors/FakeQuack.o ./quackBehaviors/MuteQuack.o ./quackBehaviors/Quack.o ./quackBehaviors/Squeak.o -o DuckSimulator $(CLANGXX_LINK_FLAGS)
	rm -v DuckSimulator.o
	cd interface && make clean
	cd ducks && make clean
	cd flyBehaviors && make clean
	cd quackBehaviors && make clean
DuckSimulator.o : DuckSimulator.cc DuckSimulator.h
	$(CXX) DuckSimulator.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	cd interface && make
Ducks.o :
	cd ducks && make
FlyBehaviors.o :
	cd flyBehaviors && make
QuackBehaviors.o :
	cd quackBehaviors && make
format :
	$(FORMAT) DuckSimulator.cc -style=file -i
	$(FORMAT) DuckSimulator.h -style=file -i
	cd interface && make format
	cd ducks && make format
	cd flyBehaviors && make format
	cd quackBehaviors && make format
clean :
	rm -v DuckSimulator