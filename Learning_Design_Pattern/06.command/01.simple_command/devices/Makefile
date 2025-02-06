###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
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
all : Light.o GarageDoor.o
Light.o : Light.cc Light.h
	$(CXX) Light.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
GarageDoor.o : GarageDoor.cc GarageDoor.h
	$(CXX) GarageDoor.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) Light.cc -style=file -i
	$(FORMAT) Light.h -style=file -i
	$(FORMAT) GarageDoor.cc -style=file -i
	$(FORMAT) GarageDoor.h -style=file -i
	$(FORMAT) devices.h -style=file -i
clean :
	rm -v Light.o GarageDoor.o