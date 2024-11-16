###########################################
#Makefile for my Android programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_Android
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template android_c android_c++
template :
	$(MAKE) -C 00.template
android_c :
	$(MAKE) -C 01.android_c
android_c++ :
	$(MAKE) -C 02.android_c++

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.android_c format
	$(MAKE) -C 02.android_c++ format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.android_c clean
	$(MAKE) -C 02.android_c++ clean