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
all : HomeTheater
HomeTheater : HomeTheater.o devices.o facade.o
	$(CXX) HomeTheater.o devices/*.o facade/*.o -o HomeTheater $(CLANGXX_LINK_FLAGS)
	rm -v HomeTheater.o
	$(MAKE) -C devices clean
	$(MAKE) -C facade clean
HomeTheater.o : HomeTheater.cc HomeTheater.h
	$(CXX) HomeTheater.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
devices.o :
	$(MAKE) -C devices
facade.o :
	$(MAKE) -C facade
format :
	$(FORMAT) HomeTheater.cc -style=file -i
	$(FORMAT) HomeTheater.h -style=file -i
	$(MAKE) -C devices format
	$(MAKE) -C facade format
clean :
	rm -v HomeTheater
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./HomeTheater