###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning\ C++
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
	cd 1.macro && make
	cd 2.regex && make
	cd 3.constructor && make
	cd 4.deconstructor && make
	cd 5.interface && make
	cd 6.interface_template && make
	cd 7.smart_pointer && make
	cd 8.const && make
	cd 9.function_template && make
	cd 10.class_template && make

format :
	cd 0.template && make format
	cd 1.macro && make format
	cd 2.regex && make format
	cd 3.constructor && make format
	cd 4.deconstructor && make format
	cd 5.interface && make format
	cd 6.interface_template && make format
	cd 7.smart_pointer && make format
	cd 8.const && make format
	cd 9.function_template && make format
	cd 10.class_template && make format

clean :
	cd 0.template && make clean
	cd 1.macro && make clean
	cd 2.regex && make clean
	cd 3.constructor && make clean
	cd 4.deconstructor && make clean
	cd 5.interface && make clean
	cd 6.interface_template && make clean
	cd 7.smart_pointer && make clean
	cd 8.const && make clean
	cd 9.function_template && make clean
	cd 10.class_template && make clean