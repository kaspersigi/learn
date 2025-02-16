###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_Native
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
LIBS = -lpthread
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
all : template v4l2 xv6_clang xv6_gcc xv6_riscv
template :
	$(MAKE) -C 00.template
v4l2 :
	$(MAKE) -C 01.v4l2
xv6_clang :
	$(MAKE) -C 02.xv6_clang
xv6_gcc :
	$(MAKE) -C 03.xv6_gcc
xv6_riscv :
	$(MAKE) -C 04.xv6_riscv

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.v4l2 format
	$(MAKE) -C 02.xv6_clang format
	$(MAKE) -C 03.xv6_gcc format
	$(MAKE) -C 04.xv6_riscv format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.v4l2 clean
	$(MAKE) -C 02.xv6_clang clean
	$(MAKE) -C 03.xv6_gcc clean
	$(MAKE) -C 04.xv6_riscv clean