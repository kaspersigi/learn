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
all : Barista
Barista : Barista.o interface.o beverages.o
	$(CXX) Barista.o interface/*.o beverages/*.o -o Barista $(CLANGXX_LINK_FLAGS)
	rm -v Barista.o
	$(MAKE) -C interface clean
	$(MAKE) -C beverages clean
Barista.o : Barista.cc Barista.h
	$(CXX) Barista.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
beverages.o :
	$(MAKE) -C beverages
format :
	$(FORMAT) Barista.cc -style=file -i
	$(FORMAT) Barista.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C beverages format
clean :
	rm -v Barista
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./Barista
scan :
	$(SCAN) make