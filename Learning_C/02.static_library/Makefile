###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
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
LIBS = -L. -lfunc
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
$(TRG) : $(OBJ) libfunc.a
	$(CC) $(OBJ) -o $(TRG) $(LIBS) $(CLANG_LINK_FLAGS) $(DEBUG)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(SRC) -c $(C_FLAGS) $(CLANG_FLAGS) $(DEBUG)
libfunc.a : func.o
	llvm-ar$(LLVM) -crv libfunc.a func.o
	rm -v func.o
func.o : func.c func.h
	$(CC) func.c -c $(C_FLAGS) $(CLANG_FLAGS) $(DEBUG)
format :
	$(FORMAT) $(SRC) -style=file -i
	$(FORMAT) func.c -style=file -i
	$(FORMAT) func.h -style=file -i
clean :
	rm -v $(TRG) libfunc.a
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)