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
all : Duck.o Turkey.o
Duck.o : Duck.cc Duck.h
	$(CXX) Duck.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Turkey.o : Turkey.cc Turkey.h
	$(CXX) Turkey.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) NonCopyable.h -style=file -i
	$(FORMAT) FlyBehavior.h -style=file -i
	$(FORMAT) QuackBehavior.h -style=file -i
	$(FORMAT) Duck.cc -style=file -i
	$(FORMAT) Duck.h -style=file -i
	$(FORMAT) Turkey.cc -style=file -i
	$(FORMAT) Turkey.h -style=file -i
clean :
	rm -v Duck.o Turkey.o
scan :
	$(SCAN) make
tidy :
	$(TIDY) Duck.cc $(TIDY_FLAGS)
	$(TIDY) Turkey.cc $(TIDY_FLAGS)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)