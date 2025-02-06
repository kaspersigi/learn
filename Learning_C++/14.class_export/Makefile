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
$(TRG) : libobject.so $(OBJ)
	$(CXX) $(OBJ) -o $(TRG) $(CLANGXX_LINK_FLAGS)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CXX) $(SRC) -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
libobject.so :
	$(MAKE) -C libobject
format :
	$(MAKE) -C libobject format
	$(FORMAT) main.cc -style=file -i
clean :
	$(MAKE) -C libobject clean
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)