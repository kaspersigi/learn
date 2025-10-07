###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o Interface.o IObject.o Object.o
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
$(TRG) : $(OBJ)
	$(CXX) $(OBJ) -o $(TRG) $(CLANGXX_LINK_FLAGS)
	rm -v $(OBJ)
main.o : main.cc IObject.h
	$(CXX) $(SRC) -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Interface.o : Interface.cc Interface.h
	$(CXX) Interface.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
IObject.o : IObject.cc IObject.h
	$(CXX) IObject.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Object.o : Object.cc Object.h
	$(CXX) Object.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) $(SRC) -style=file -i
	$(FORMAT) Interface.h -style=file -i
	$(FORMAT) Interface.cc -style=file -i
	$(FORMAT) IObject.h -style=file -i
	$(FORMAT) IObject.cc -style=file -i
	$(FORMAT) Object.h -style=file -i
	$(FORMAT) Object.cc -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)
scan :
	$(SCAN) make