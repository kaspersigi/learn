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
	rm -v DarkRoast.o Decaf.o Espresso.o HouseBlend.o