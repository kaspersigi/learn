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
all : SimpleRemote
SimpleRemote : SimpleRemote.o commands.o control.o devices.o
	$(CXX) SimpleRemote.o commands/*.o control/*.o devices/*.o -o SimpleRemote $(CLANGXX_LINK_FLAGS)
	rm -v SimpleRemote.o
	$(MAKE) -C commands clean
	$(MAKE) -C control clean
	$(MAKE) -C devices clean
SimpleRemote.o : SimpleRemote.cc SimpleRemote.h
	$(CXX) SimpleRemote.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
commands.o :
	$(MAKE) -C commands
control.o :
	$(MAKE) -C control
devices.o :
	$(MAKE) -C devices
format :
	$(FORMAT) SimpleRemote.cc -style=file -i
	$(FORMAT) SimpleRemote.h -style=file -i
	$(MAKE) -C commands format
	$(MAKE) -C control format
	$(MAKE) -C devices format
clean :
	rm -v SimpleRemote
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./SimpleRemote