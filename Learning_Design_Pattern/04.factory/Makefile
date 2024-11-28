###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
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
all : simple_factory static_factory factory_method abstract_factory
simple_factory :
	$(MAKE) -C 01.simple_factory
static_factory :
	$(MAKE) -C 02.static_factory
factory_method :
	$(MAKE) -C 03.factory_method
abstract_factory :
	$(MAKE) -C 04.abstract_factory

format :
	$(MAKE) -C 01.simple_factory format
	$(MAKE) -C 02.static_factory format
	$(MAKE) -C 03.factory_method format
	$(MAKE) -C 04.abstract_factory format

clean :
	$(MAKE) -C 01.simple_factory clean
	$(MAKE) -C 02.static_factory clean
	$(MAKE) -C 03.factory_method clean
	$(MAKE) -C 04.abstract_factory clean