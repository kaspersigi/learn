###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
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
all : barista barista_with_hook
barista :
	$(MAKE) -C 01.barista
barista_with_hook :
	$(MAKE) -C 02.barista_with_hook

format :
	$(MAKE) -C 01.barista format
	$(MAKE) -C 02.barista_with_hook format

clean :
	$(MAKE) -C 01.barista clean
	$(MAKE) -C 02.barista_with_hook clean