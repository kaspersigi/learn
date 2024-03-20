###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_Native
LLVM = -17
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template v4l2 malloc new xv6_clang
template :
	$(MAKE) -C 00.template
v4l2 :
	$(MAKE) -C 01.v4l2
android_c :
	$(MAKE) -C 02.android_c
android_c++ :
	$(MAKE) -C 03.android_c++
rust :
	$(MAKE) -C 04.rust
malloc :
	$(MAKE) -C 05.malloc
new :
	$(MAKE) -C 06.new
xv6_clang :
	$(MAKE) -C 07.xv6_clang
xv6_gcc :
	$(MAKE) -C 08.xv6_gcc

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.v4l2 format
	$(MAKE) -C 02.android_c format
	$(MAKE) -C 03.android_c++ format
	# $(MAKE) -C 04.rust format
	$(MAKE) -C 05.malloc format
	$(MAKE) -C 06.new format
	$(MAKE) -C 07.xv6_clang format
	$(MAKE) -C 08.xv6_gcc format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.v4l2 clean
	# $(MAKE) -C 02.android_c clean
	# $(MAKE) -C 03.android_c++ clean
	# $(MAKE) -C 04.rust clean
	$(MAKE) -C 05.malloc clean
	$(MAKE) -C 06.new clean
	$(MAKE) -C 07.xv6_clang clean
	# $(MAKE) -C 08.xv6_gcc clean