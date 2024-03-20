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
all : FakeQuack.o Gobble.o MuteQuack.o Quack.o Squeak.o
FakeQuack.o : FakeQuack.cc FakeQuack.h
	$(CXX) FakeQuack.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Gobble.o : Gobble.cc Gobble.h
	$(CXX) Gobble.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
MuteQuack.o : MuteQuack.cc MuteQuack.h
	$(CXX) MuteQuack.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Quack.o : Quack.cc Quack.h
	$(CXX) Quack.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Squeak.o : Squeak.cc Squeak.h
	$(CXX) Squeak.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) quackBehaviors.h -style=file -i
	$(FORMAT) FakeQuack.cc -style=file -i
	$(FORMAT) FakeQuack.h -style=file -i
	$(FORMAT) Gobble.cc -style=file -i
	$(FORMAT) Gobble.h -style=file -i
	$(FORMAT) MuteQuack.cc -style=file -i
	$(FORMAT) MuteQuack.h -style=file -i
	$(FORMAT) Quack.cc -style=file -i
	$(FORMAT) Quack.h -style=file -i
	$(FORMAT) Squeak.cc -style=file -i
	$(FORMAT) Squeak.h -style=file -i
clean :
	rm -v FakeQuack.o Gobble.o MuteQuack.o Quack.o Squeak.o