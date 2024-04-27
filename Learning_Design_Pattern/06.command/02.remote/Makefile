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
all : Remote
Remote : Remote.o commands.o control.o devices.o
	$(CXX) Remote.o commands/*.o control/*.o devices/*.o -o Remote $(CLANGXX_LINK_FLAGS)
	rm -v Remote.o
	$(MAKE) -C commands clean
	$(MAKE) -C control clean
	$(MAKE) -C devices clean
Remote.o : Remote.cc Remote.h
	$(CXX) Remote.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
commands.o :
	$(MAKE) -C commands
control.o :
	$(MAKE) -C control
devices.o :
	$(MAKE) -C devices
format :
	$(FORMAT) Remote.cc -style=file -i
	$(FORMAT) Remote.h -style=file -i
	$(MAKE) -C commands format
	$(MAKE) -C control format
	$(MAKE) -C devices format
clean :
	rm -v Remote
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./Remote