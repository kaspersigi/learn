###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o ftrace.o
SRC = main.c ftrace.h
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
LIBS = -L../lib/$(shell uname -m) -lOpenCL -Wl,-rpath=../lib/$(shell uname -m)
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
$(TRG) : $(OBJ)
	$(CC) $(OBJ) -o $(TRG) $(CLANG_LINK_FLAGS) $(LIBS) $(DEBUG)
	rm -v $(OBJ)
main.o : main.c
	$(CC) main.c -c $(C_FLAGS) $(CLANG_FLAGS) $(DEBUG) -I../inc -DCL_TARGET_OPENCL_VERSION=300
ftrace.o : ftrace.c
	$(CC) ftrace.c -c $(C_FLAGS) $(CLANG_FLAGS) $(DEBUG)
format :
	$(FORMAT) ftrace.c -style=file -i
	$(FORMAT) ftrace.h -style=file -i
	$(FORMAT) main.c -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)