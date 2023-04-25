###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning\ C++
ARCH = $(shell llvm-config --host-target)
CC = /usr/bin/clang --target=$(ARCH)
CXX = /usr/bin/clang++ --target=$(ARCH)
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
all : template binary_search remove_element squares_of_a_sorted_array
template :
	$(MAKE) -C 00.template
binary_search :
	$(MAKE) -C 01.binary_search
remove_element :
	$(MAKE) -C 02.remove_element
squares_of_a_sorted_array :
	$(MAKE) -C 03.squares_of_a_sorted_array

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.binary_search format
	$(MAKE) -C 02.remove_element format
	$(MAKE) -C 03.squares_of_a_sorted_array format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.binary_search clean
	$(MAKE) -C 02.remove_element clean
	$(MAKE) -C 03.squares_of_a_sorted_array clean