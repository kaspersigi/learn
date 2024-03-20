###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
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
$(TRG) : $(OBJ) libfunc.a
	$(CC) $(OBJ) -o $(TRG) -L. -lfunc
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(SRC) -c $(C_FLAGS) $(DEBUG)
libfunc.a : func.o
	llvm-ar$(LLVM) -crv libfunc.a func.o
	rm -v func.o
func.o : func.c func.h
	$(CC) func.c -c $(C_FLAGS) $(DEBUG)
format :
	$(FORMAT) main.c -style=file -i
	$(FORMAT) func.c -style=file -i
	$(FORMAT) func.h -style=file -i
clean :
	rm -v $(TRG) libfunc.a
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)