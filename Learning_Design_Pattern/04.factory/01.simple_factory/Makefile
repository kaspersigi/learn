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
all : Pizza
Pizza : Pizza.o interface.o factory.o pizzas.o store.o
	$(CXX) Pizza.o interface/*.o factory/*.o pizzas/*.o store/*.o -o Pizza $(CLANGXX_LINK_FLAGS)
	rm -v Pizza.o
	$(MAKE) -C interface clean
	$(MAKE) -C factory clean
	$(MAKE) -C pizzas clean
	$(MAKE) -C store clean
Pizza.o : Pizza.cc Pizza.h
	$(CXX) Pizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
factory.o :
	$(MAKE) -C factory
pizzas.o :
	$(MAKE) -C pizzas
store.o :
	$(MAKE) -C store
format :
	$(FORMAT) Pizza.cc -style=file -i
	$(FORMAT) Pizza.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C factory format
	$(MAKE) -C pizzas format
	$(MAKE) -C store format
clean :
	rm -v Pizza
scan :
	$(SCAN) make
tidy :
	$(TIDY) Pizza.cc $(TIDY_FLAGS)
	$(MAKE) -C interface tidy
	$(MAKE) -C factory tidy
	$(MAKE) -C pizzas tidy
	$(MAKE) -C store tidy
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)