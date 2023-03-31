###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning\ Native
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
all : template driver
template :
	$(MAKE) -C 00.template
driver :
	$(MAKE) -C 01.driver

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.driver format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.driver clean

style :
	clang-format -style=webkit -dump-config > .clang-format