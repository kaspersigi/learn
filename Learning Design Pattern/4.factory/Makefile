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
all :
	cd 1.simple_factory && make
	cd 2.static_factory && make
	cd 3.factory_method && make
	# cd 4.abstract_factory && make

format :
	cd 1.simple_factory && make format
	cd 2.static_factory && make format
	cd 3.factory_method && make format
	# cd 4.abstract_factory && make format

clean :
	cd 1.simple_factory && make clean
	cd 2.static_factory && make clean
	cd 3.factory_method && make clean
	# cd 4.abstract_factory && make clean