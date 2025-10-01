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
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
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
all : DarkRoast.o Decaf.o Espresso.o HouseBlend.o
DarkRoast.o : DarkRoast.cc DarkRoast.h
	$(CXX) DarkRoast.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Decaf.o : Decaf.cc Decaf.h
	$(CXX) Decaf.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Espresso.o : Espresso.cc Espresso.h
	$(CXX) Espresso.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
HouseBlend.o : HouseBlend.cc HouseBlend.h
	$(CXX) HouseBlend.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) components.h -style=file -i
	$(FORMAT) DarkRoast.cc -style=file -i
	$(FORMAT) DarkRoast.h -style=file -i
	$(FORMAT) Decaf.cc -style=file -i
	$(FORMAT) Decaf.h -style=file -i
	$(FORMAT) Espresso.cc -style=file -i
	$(FORMAT) Espresso.h -style=file -i
	$(FORMAT) HouseBlend.cc -style=file -i
	$(FORMAT) HouseBlend.h -style=file -i
clean :
	rm -v DarkRoast.o Decaf.o Espresso.o HouseBlend.o
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)
scan :
	$(SCAN) make