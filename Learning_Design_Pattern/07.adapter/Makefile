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
all : Adapter
Adapter : Adapter.o interface.o ducks.o turkeys.o flyBehaviors.o quackBehaviors.o adapters.o
	$(CXX) Adapter.o interface/*.o ducks/*.o turkeys/*.o flyBehaviors/*.o quackBehaviors/*.o adapters/*.o -o Adapter $(CLANGXX_LINK_FLAGS)
	rm -v Adapter.o
	$(MAKE) -C interface clean
	$(MAKE) -C ducks clean
	$(MAKE) -C turkeys clean
	$(MAKE) -C flyBehaviors clean
	$(MAKE) -C quackBehaviors clean
	$(MAKE) -C adapters clean
Adapter.o : Adapter.cc Adapter.h
	$(CXX) Adapter.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
ducks.o :
	$(MAKE) -C ducks
turkeys.o :
	$(MAKE) -C turkeys
flyBehaviors.o :
	$(MAKE) -C flyBehaviors
quackBehaviors.o :
	$(MAKE) -C quackBehaviors
adapters.o :
	$(MAKE) -C adapters
format :
	$(FORMAT) Adapter.cc -style=file -i
	$(FORMAT) Adapter.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C ducks format
	$(MAKE) -C turkeys format
	$(MAKE) -C flyBehaviors format
	$(MAKE) -C quackBehaviors format
	$(MAKE) -C adapters format
clean :
	rm -v Adapter
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./Adapter