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
all : Coffee.o Tea.o
Coffee.o : Coffee.cc Coffee.h
	$(CXX) Coffee.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Tea.o : Tea.cc Tea.h
	$(CXX) Tea.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) Coffee.cc -style=file -i
	$(FORMAT) Coffee.h -style=file -i
	$(FORMAT) Tea.cc -style=file -i
	$(FORMAT) Tea.h -style=file -i
	$(FORMAT) beverages.h -style=file -i
clean :
	rm -v Coffee.o Tea.o