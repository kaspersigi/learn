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
all : CeilingFan.o Light.o
CeilingFan.o : CeilingFan.cc CeilingFan.h
	$(CXX) CeilingFan.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Light.o : Light.cc Light.h
	$(CXX) Light.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) CeilingFan.cc -style=file -i
	$(FORMAT) CeilingFan.h -style=file -i
	$(FORMAT) Light.cc -style=file -i
	$(FORMAT) Light.h -style=file -i
	$(FORMAT) devices.h -style=file -i
clean :
	rm -v CeilingFan.o Light.o