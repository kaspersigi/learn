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
$(TRG) : libobject.so $(OBJ)
	$(CXX) $(OBJ) -o $(TRG) $(CLANGXX_LINK_FLAGS) $(DEBUG)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CXX) $(SRC) -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
libobject.so :
	$(MAKE) -C libobject
format :
	$(MAKE) -C libobject format
	$(FORMAT) $(SRC) -style=file -i
clean :
	$(MAKE) -C libobject clean
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)