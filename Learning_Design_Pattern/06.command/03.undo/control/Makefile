###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
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
all : RemoteControlWithUndo.o
RemoteControlWithUndo.o : RemoteControlWithUndo.cc RemoteControlWithUndo.h
	$(CXX) RemoteControlWithUndo.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) RemoteControlWithUndo.cc -style=file -i
	$(FORMAT) RemoteControlWithUndo.h -style=file -i
clean :
	rm -v RemoteControlWithUndo.o