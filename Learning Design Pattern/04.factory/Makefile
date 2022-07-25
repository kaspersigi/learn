###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
CC = /usr/bin/clang
CXX = /usr/bin/clang++
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -O3
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all :
	$(MAKE) -C 01.simple_factory
	$(MAKE) -C 02.static_factory
	$(MAKE) -C 03.factory_method
	# $(MAKE) -C 04.abstract_factory

format :
	$(MAKE) -C 01.simple_factory format
	$(MAKE) -C 02.static_factory format
	$(MAKE) -C 03.factory_method format
	# $(MAKE) -C 4.abstract_factory format

clean :
	$(MAKE) -C 01.simple_factory clean
	$(MAKE) -C 02.static_factory clean
	$(MAKE) -C 03.factory_method clean
	# $(MAKE) -C 04.abstract_factory clean