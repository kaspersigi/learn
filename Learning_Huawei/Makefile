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
all : hj000 hj001 hj002 hj003 hj004 hj005 hj006 hj007 hj008
hj000 :
	$(MAKE) -C 000
hj001 :
	$(MAKE) -C 001
hj002 :
	$(MAKE) -C 002
hj003 :
	$(MAKE) -C 003
hj004 :
	$(MAKE) -C 004
hj005 :
	$(MAKE) -C 005
hj006 :
	$(MAKE) -C 006
hj007 :
	$(MAKE) -C 007
hj008 :
	$(MAKE) -C 008

format :
	$(MAKE) -C 000 format
	$(MAKE) -C 001 format
	$(MAKE) -C 002 format
	$(MAKE) -C 003 format
	$(MAKE) -C 004 format
	$(MAKE) -C 005 format
	$(MAKE) -C 006 format
	$(MAKE) -C 007 format
	$(MAKE) -C 008 format

clean :
	$(MAKE) -C 000 clean
	$(MAKE) -C 001 clean
	$(MAKE) -C 002 clean
	$(MAKE) -C 003 clean
	$(MAKE) -C 004 clean
	$(MAKE) -C 005 clean
	$(MAKE) -C 006 clean
	$(MAKE) -C 007 clean
	$(MAKE) -C 008 clean