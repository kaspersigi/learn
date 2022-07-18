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
	cd 0.template && make
	cd 1.strategy && make
	cd 2.observer && make
	cd 3.decorator && make
	cd 4.factory && make

format :
	cd 0.template && make format
	cd 1.strategy && make format
	cd 2.observer && make format
	cd 3.decorator && make format
	cd 4.factory && make format

clean :
	cd 0.template && make clean
	cd 1.strategy && make clean
	cd 2.observer && make clean
	cd 3.decorator && make clean
	cd 4.factory && make clean