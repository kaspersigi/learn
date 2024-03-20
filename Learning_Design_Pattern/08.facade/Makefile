###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = -17
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

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