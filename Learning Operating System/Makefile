###########################################
#Makefile for my assembler programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning\ Operating\ System
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
all : template protected function_call
template :
	$(MAKE) -C 00.template
protected :
	$(MAKE) -C 01.protected
function_call :
	$(MAKE) -C 02.function_call

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.protected clean
	$(MAKE) -C 02.function_call clean