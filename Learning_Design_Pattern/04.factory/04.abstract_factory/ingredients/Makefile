###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = 17
CONFIG = llvm-config-$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang-$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++-$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format-$(LLVM)
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : cheese.o clams.o dough.o pepperoni.o sauce.o veggies.o
cheese.o :
	$(MAKE) -C cheese
clams.o :
	$(MAKE) -C clams
dough.o :
	$(MAKE) -C dough
pepperoni.o :
	$(MAKE) -C pepperoni
sauce.o :
	$(MAKE) -C sauce
veggies.o :
	$(MAKE) -C veggies
format :
	$(MAKE) -C cheese format
	$(MAKE) -C clams format
	$(MAKE) -C dough format
	$(MAKE) -C pepperoni format
	$(MAKE) -C sauce format
	$(MAKE) -C veggies format
clean :
	$(MAKE) -C cheese clean
	$(MAKE) -C clams clean
	$(MAKE) -C dough clean
	$(MAKE) -C pepperoni clean
	$(MAKE) -C sauce clean
	$(MAKE) -C veggies clean