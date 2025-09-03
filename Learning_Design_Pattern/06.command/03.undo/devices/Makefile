###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = -21
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
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

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