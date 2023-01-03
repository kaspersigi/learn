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
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
ARCH = -m32

.PHONY : all
all : template protected function_call paging ia32e xv6
template :
	$(MAKE) -C 00.template
protected :
	$(MAKE) -C 01.protected
function_call :
	$(MAKE) -C 02.function_call
paging :
	$(MAKE) -C 03.paging
ia32e :
	$(MAKE) -C 04.ia32e
xv6 :
	$(MAKE) -C 05.xv6

format :
	$(MAKE) -C 05.xv6 format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.protected clean
	$(MAKE) -C 02.function_call clean
	$(MAKE) -C 03.paging clean
	$(MAKE) -C 04.ia32e clean
	$(MAKE) -C 05.xv6 clean