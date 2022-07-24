###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning\ Design\ Pattern
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
all :
	cd 00.template && make
	cd 01.strategy && make
	cd 02.observer && make
	cd 03.decorator && make
	cd 04.factory && make

format :
	cd 00.template && make format
	cd 01.strategy && make format
	cd 02.observer && make format
	cd 03.decorator && make format
	cd 04.factory && make format

clean :
	cd 00.template && make clean
	cd 01.strategy && make clean
	cd 02.observer && make clean
	cd 03.decorator && make clean
	cd 04.factory && make clean