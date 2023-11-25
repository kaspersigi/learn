###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_Native
ARCH = $(shell llvm-config --host-target)
CC = /usr/bin/clang --target=$(ARCH)
CXX = /usr/bin/clang++ --target=$(ARCH)
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c11 -Wall -Wno-unused
CXX_FLAGS = -std=c++11 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template v4l2 module module_param export_symbol
template :
	$(MAKE) -C 00.template
v4l2 :
	$(MAKE) -C 01.v4l2
module :
	$(MAKE) -C 02.module
module_param :
	$(MAKE) -C 03.module_param
export_symbol :
	$(MAKE) -C 04.export_symbol

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.v4l2 format
	$(MAKE) -C 02.module format
	$(MAKE) -C 03.module_param format
	$(MAKE) -C 04.export_symbol format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.v4l2 clean
	$(MAKE) -C 02.module clean
	$(MAKE) -C 03.module_param clean
	$(MAKE) -C 04.export_symbol clean

style :
	clang-format -style=webkit -dump-config > .clang-format