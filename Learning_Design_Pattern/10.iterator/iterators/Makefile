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
TIDY = /usr/bin/clang-tidy$(LLVM) -quiet
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
TIDY_FLAGS = -- --target=$(ARCH) $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)

.PHONY : all
all : DinerMenuIterator.o PancakeHouseMenuIterator.o
DinerMenuIterator.o : DinerMenuIterator.cc DinerMenuIterator.h
	$(CXX) DinerMenuIterator.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
PancakeHouseMenuIterator.o : PancakeHouseMenuIterator.cc PancakeHouseMenuIterator.h
	$(CXX) PancakeHouseMenuIterator.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) DinerMenuIterator.cc -style=file -i
	$(FORMAT) DinerMenuIterator.h -style=file -i
	$(FORMAT) PancakeHouseMenuIterator.cc -style=file -i
	$(FORMAT) PancakeHouseMenuIterator.h -style=file -i
	$(FORMAT) iterators.h -style=file -i
clean :
	rm -vf DinerMenuIterator.o PancakeHouseMenuIterator.o
scan :
	$(SCAN) make
tidy :
	$(TIDY) DinerMenuIterator.cc $(TIDY_FLAGS)
	$(TIDY) PancakeHouseMenuIterator.cc $(TIDY_FLAGS)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)