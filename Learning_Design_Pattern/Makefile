###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning_Design_Pattern
ARCH = $(shell llvm-config --host-target)
LLVM = -19
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
all : template.o strategy observer decorator factory singleton command adapter facade template iterator
template.o :
	$(MAKE) -C 00.template
strategy :
	$(MAKE) -C 01.strategy
observer :
	$(MAKE) -C 02.observer
decorator :
	$(MAKE) -C 03.decorator
factory :
	$(MAKE) -C 04.factory
singleton :
	$(MAKE) -C 05.singleton
command :
	$(MAKE) -C 06.command
adapter :
	$(MAKE) -C 07.adapter
facade :
	$(MAKE) -C 08.facade
template :
	$(MAKE) -C 09.template
iterator :
	$(MAKE) -C 10.iterator

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.strategy format
	$(MAKE) -C 02.observer format
	$(MAKE) -C 03.decorator format
	$(MAKE) -C 04.factory format
	$(MAKE) -C 05.singleton format
	$(MAKE) -C 06.command format
	$(MAKE) -C 07.adapter format
	$(MAKE) -C 08.facade format
	$(MAKE) -C 09.template format
	$(MAKE) -C 10.iterator format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.strategy clean
	$(MAKE) -C 02.observer clean
	$(MAKE) -C 03.decorator clean
	$(MAKE) -C 04.factory clean
	$(MAKE) -C 05.singleton clean
	$(MAKE) -C 06.command clean
	$(MAKE) -C 07.adapter clean
	$(MAKE) -C 08.facade clean
	$(MAKE) -C 09.template clean
	$(MAKE) -C 10.iterator clean