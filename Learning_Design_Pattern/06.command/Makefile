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
all : simple_command remote undo
simple_command :
	$(MAKE) -C 01.simple_command
remote :
	$(MAKE) -C 02.remote
undo :
	$(MAKE) -C 03.undo

format :
	$(MAKE) -C 01.simple_command format
	$(MAKE) -C 02.remote format
	$(MAKE) -C 03.undo format

clean :
	$(MAKE) -C 01.simple_command clean
	$(MAKE) -C 02.remote clean
	$(MAKE) -C 03.undo clean