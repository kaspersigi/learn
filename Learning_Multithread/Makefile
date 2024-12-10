###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning_C++
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template ques1 ques2 ques3 ques4 ques5 ques6
template :
	$(MAKE) -C 00.template
ques1 :
	$(MAKE) -C 01.ques1
ques2 :
	$(MAKE) -C 02.ques2
ques3 :
	$(MAKE) -C 03.ques3
ques4 :
	$(MAKE) -C 04.ques4
ques5 :
	$(MAKE) -C 05.ques5
ques6 :
	$(MAKE) -C 06.ques6

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.ques1 format
	$(MAKE) -C 02.ques2 format
	$(MAKE) -C 03.ques3 format
	$(MAKE) -C 04.ques4 format
	$(MAKE) -C 05.ques5 format
	$(MAKE) -C 06.ques6 format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.ques1 clean
	$(MAKE) -C 02.ques2 clean
	$(MAKE) -C 03.ques3 clean
	$(MAKE) -C 04.ques4 clean
	$(MAKE) -C 05.ques5 clean
	$(MAKE) -C 06.ques6 clean