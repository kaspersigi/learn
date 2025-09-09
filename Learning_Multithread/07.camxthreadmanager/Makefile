###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o ftrace.o threadcore.o threadmanager.o
SRC = main.cc ftrace.cc threadcore.cc threadmanager.cc
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -flto -O3
LIBS = -L$(shell uname -m) -lspdlog
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
$(TRG) : $(OBJ)
	$(CC) $(OBJ) -o $(TRG) $(CLANGXX_LINK_FLAGS) $(LIBS)
	rm -v $(OBJ)
main.o : main.cc
	$(CC) main.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG) -I ./inc
ftrace.o : ftrace.cc
	$(CC) ftrace.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG) -I ./inc
threadcore.o : threadcore.cc
	$(CC) threadcore.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG) -I ./inc
threadmanager.o : threadmanager.cc
	$(CC) threadmanager.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG) -I ./inc
format :
	$(FORMAT) main.cc -style=file -i
	$(FORMAT) ftrace.h -style=file -i
	$(FORMAT) ftrace.cc -style=file -i
	$(FORMAT) threadcore.h -style=file -i
	$(FORMAT) threadcore.cc -style=file -i
	$(FORMAT) threadmanager.h -style=file -i
	$(FORMAT) threadmanager.cc -style=file -i
	$(FORMAT) types.h -style=file -i
	$(FORMAT) imonitorclient.h -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)