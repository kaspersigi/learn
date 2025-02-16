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
LIBS = -ldl -L. -lfunc -Wl,-rpath=.
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
$(TRG) : $(OBJ) libfunc.so
	$(CC) $(OBJ) -o $(TRG) $(LIBS) $(DEBUG)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(SRC) -c $(C_FLAGS) $(DEBUG)
libfunc.so : func.o
	$(CC) func.o -o libfunc.so $(DEBUG) -shared
	rm -v func.o
func.o : func.c func.h
	$(CC) func.c -c $(C_FLAGS) $(DEBUG) -fPIC
format :
	$(FORMAT) $(SRC) -style=file -i
	$(FORMAT) func.c -style=file -i
	$(FORMAT) func.h -style=file -i
clean :
	rm -v $(TRG) libfunc.so
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)