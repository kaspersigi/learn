###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = -19
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
	rm -v FlyNoWay.o FlyRocketPowered.o FlyWithWings.o