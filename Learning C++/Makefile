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
	cd 00.template && make
	cd 01.macro && make
	cd 02.regex && make
	cd 03.constructor && make
	cd 04.deconstructor && make
	cd 05.interface && make
	cd 06.interface_template && make
	cd 07.smart_pointer && make
	cd 08.const && make
	cd 09.function_template && make
	cd 10.class_template && make
	cd 11.threadpool && make

format :
	cd 00.template && make format
	cd 01.macro && make format
	cd 02.regex && make format
	cd 03.constructor && make format
	cd 04.deconstructor && make format
	cd 05.interface && make format
	cd 06.interface_template && make format
	cd 07.smart_pointer && make format
	cd 08.const && make format
	cd 09.function_template && make format
	cd 10.class_template && make format
	cd 11.threadpool && make format

clean :
	cd 00.template && make clean
	cd 01.macro && make clean
	cd 02.regex && make clean
	cd 03.constructor && make clean
	cd 04.deconstructor && make clean
	cd 05.interface && make clean
	cd 06.interface_template && make clean
	cd 07.smart_pointer && make clean
	cd 08.const && make clean
	cd 09.function_template && make clean
	cd 10.class_template && make clean
	cd 11.threadpool && make clean