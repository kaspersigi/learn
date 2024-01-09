###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_Driver
ARCH =
CROSS_COMPILE = arm-linux-gnueabi-
CC = /usr/bin/$(CROSS_COMPILE)gcc
CXX = /usr/bin/$(CROSS_COMPILE)g++
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
all : template module module_param export_symbol char
template :
	$(MAKE) -C 00.template
module :
	$(MAKE) -C 01.module
module_param :
	$(MAKE) -C 02.module_param
export_symbol :
	$(MAKE) -C 03.export_symbol
char :
	$(MAKE) -C 04.char

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.module format
	$(MAKE) -C 02.module_param format
	$(MAKE) -C 03.export_symbol format
	$(MAKE) -C 04.char format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.module clean
	$(MAKE) -C 02.module_param clean
	$(MAKE) -C 03.export_symbol clean
	$(MAKE) -C 04.char clean