###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
ARCH = $(shell llvm-config --host-target)
CC = /usr/bin/clang --target=$(ARCH)
CXX = /usr/bin/clang++ --target=$(ARCH)
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c2x -Wall -Wno-unused
CXX_FLAGS = -std=c++2b -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : MarinaraSauce.o PlumTomatoSauce.o
MarinaraSauce.o : MarinaraSauce.cc MarinaraSauce.h
	$(CXX) MarinaraSauce.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
PlumTomatoSauce.o : PlumTomatoSauce.cc PlumTomatoSauce.h
	$(CXX) PlumTomatoSauce.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) MarinaraSauce.cc -style=file -i
	$(FORMAT) MarinaraSauce.h -style=file -i
	$(FORMAT) PlumTomatoSauce.cc -style=file -i
	$(FORMAT) PlumTomatoSauce.h -style=file -i
clean :
	rm -v MarinaraSauce.o PlumTomatoSauce.o