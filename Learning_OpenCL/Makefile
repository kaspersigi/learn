###########################################
#Makefile for my OpenCL programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
LLVM = -20
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -flto -O3
LIBS = -L./lib/$(shell uname -m) -lOpenCL -Wl,-rpath=./lib/$(shell uname -m)
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
all : clinfo demo
clinfo :
	$(MAKE) -C 00.clinfo
demo :
	$(MAKE) -C 01.demo

format :
	$(MAKE) -C 00.clinfo format
	$(MAKE) -C 01.demo format

clean :
	$(MAKE) -C 00.clinfo clean
	$(MAKE) -C 01.demo clean