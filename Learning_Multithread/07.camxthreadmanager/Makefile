###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o threadmanager.o ftrace.o
SRC = main.cc threadmanager.cc ftrace.cc
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
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
$(TRG) : $(OBJ)
	$(CXX) $(OBJ) -o $(TRG) $(CLANGXX_LINK_FLAGS) $(LIBS)
	rm -v $(OBJ)
threadmanager.o : threadmanager.cc threadmanager.h
	$(CXX) threadmanager.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ftrace.o : ftrace.cc ftrace.h
	$(CXX) ftrace.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
main.o : main.cc
	$(CXX) main.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) threadmanager.h -style=file -i
	$(FORMAT) threadmanager.cc -style=file -i
	$(FORMAT) ftrace.h -style=file -i
	$(FORMAT) ftrace.cc -style=file -i
	$(FORMAT) main.cc -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)