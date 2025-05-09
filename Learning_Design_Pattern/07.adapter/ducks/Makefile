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
all : DecoyDuck.o MallardDuck.o ModelDuck.o RedHeadDuck.o RubberDuck.o
DecoyDuck.o : DecoyDuck.cc DecoyDuck.h
	$(CXX) DecoyDuck.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
MallardDuck.o : MallardDuck.cc MallardDuck.h
	$(CXX) MallardDuck.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ModelDuck.o : ModelDuck.cc ModelDuck.h
	$(CXX) ModelDuck.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
RedHeadDuck.o : RedHeadDuck.cc RedHeadDuck.h
	$(CXX) RedHeadDuck.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
RubberDuck.o : RubberDuck.cc RubberDuck.h
	$(CXX) RubberDuck.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) ducks.h -style=file -i
	$(FORMAT) DecoyDuck.cc -style=file -i
	$(FORMAT) DecoyDuck.h -style=file -i
	$(FORMAT) MallardDuck.cc -style=file -i
	$(FORMAT) MallardDuck.h -style=file -i
	$(FORMAT) ModelDuck.cc -style=file -i
	$(FORMAT) ModelDuck.h -style=file -i
	$(FORMAT) RedHeadDuck.cc -style=file -i
	$(FORMAT) RedHeadDuck.h -style=file -i
	$(FORMAT) RubberDuck.cc -style=file -i
	$(FORMAT) RubberDuck.h -style=file -i
clean :
	rm -v DecoyDuck.o MallardDuck.o ModelDuck.o RedHeadDuck.o RubberDuck.o