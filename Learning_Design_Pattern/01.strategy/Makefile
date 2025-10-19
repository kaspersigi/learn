###########################################
#Makefile for my C++ programs
###########################################

TRG = DuckSimulator
OBJ = DuckSimulator.o
SRC = DuckSimulator.cc
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
TIDY = /usr/bin/clang-tidy$(LLVM)
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
all : DuckSimulator
DuckSimulator : DuckSimulator.o interface.o ducks.o flyBehaviors.o quackBehaviors.o
	$(CXX) DuckSimulator.o interface/*.o ducks/*.o flyBehaviors/*.o quackBehaviors/*.o -o DuckSimulator $(CLANGXX_LINK_FLAGS)
	rm -v DuckSimulator.o
	$(MAKE) -C interface clean
	$(MAKE) -C ducks clean
	$(MAKE) -C flyBehaviors clean
	$(MAKE) -C quackBehaviors clean
DuckSimulator.o : DuckSimulator.cc DuckSimulator.h
	$(CXX) DuckSimulator.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
ducks.o :
	$(MAKE) -C ducks
flyBehaviors.o :
	$(MAKE) -C flyBehaviors
quackBehaviors.o :
	$(MAKE) -C quackBehaviors
format :
	$(FORMAT) DuckSimulator.cc -style=file -i
	$(FORMAT) DuckSimulator.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C ducks format
	$(MAKE) -C flyBehaviors format
	$(MAKE) -C quackBehaviors format
clean :
	rm -v DuckSimulator
scan :
	$(SCAN) make
tidy :
	$(TIDY) DuckSimulator.cc $(TIDY_FLAGS)
	$(MAKE) -C interface tidy
	$(MAKE) -C ducks tidy
	$(MAKE) -C flyBehaviors tidy
	$(MAKE) -C quackBehaviors tidy
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)