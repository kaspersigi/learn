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
all : pointer smart_pointer
pointer :
	$(MAKE) -C 01.pointer
smart_pointer :
	$(MAKE) -C 02.smart_pointer

format :
	$(MAKE) -C 01.pointer format
	$(MAKE) -C 02.smart_pointer format

clean :
	$(MAKE) -C 01.pointer clean
	$(MAKE) -C 02.smart_pointer clean