###########################################
#Makefile for my C++ programs
###########################################

TRG = libobject.so
OBJ = IObject.o Object.o
SRC = IObject.cc Object.cc
LLVM = -19
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
$(TRG) : $(OBJ)
	$(CXX) $(OBJ) -o $(TRG) $(CLANGXX_FLAGS) $(DEBUG) -shared
	rm -v $(OBJ)
IObject.o : IObject.cc IObject.h
	$(CXX) IObject.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG) -fPIC
Object.o : Object.cc Object.h
	$(CXX) Object.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG) -fPIC
format :
	$(FORMAT) interface.h -style=file -i
	$(FORMAT) IObject.h -style=file -i
	$(FORMAT) IObject.cc -style=file -i
	$(FORMAT) Object.h -style=file -i
	$(FORMAT) Object.cc -style=file -i
clean :
	rm -v $(TRG)