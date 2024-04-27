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
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : ThickCrustDough.o ThinCrustDough.o
ThickCrustDough.o : ThickCrustDough.cc ThickCrustDough.h
	$(CXX) ThickCrustDough.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ThinCrustDough.o : ThinCrustDough.cc ThinCrustDough.h
	$(CXX) ThinCrustDough.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) ThickCrustDough.cc -style=file -i
	$(FORMAT) ThickCrustDough.h -style=file -i
	$(FORMAT) ThinCrustDough.cc -style=file -i
	$(FORMAT) ThinCrustDough.h -style=file -i
clean :
	rm -v ThickCrustDough.o ThinCrustDough.o