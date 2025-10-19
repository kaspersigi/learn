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
all : cheese.o clams.o dough.o pepperoni.o sauce.o veggies.o
cheese.o :
	$(MAKE) -C cheese
clams.o :
	$(MAKE) -C clams
dough.o :
	$(MAKE) -C dough
pepperoni.o :
	$(MAKE) -C pepperoni
sauce.o :
	$(MAKE) -C sauce
veggies.o :
	$(MAKE) -C veggies
format :
	$(MAKE) -C cheese format
	$(MAKE) -C clams format
	$(MAKE) -C dough format
	$(MAKE) -C pepperoni format
	$(MAKE) -C sauce format
	$(MAKE) -C veggies format
clean :
	$(MAKE) -C cheese clean
	$(MAKE) -C clams clean
	$(MAKE) -C dough clean
	$(MAKE) -C pepperoni clean
	$(MAKE) -C sauce clean
	$(MAKE) -C veggies clean
scan :
	$(MAKE) -C cheese scan
	$(MAKE) -C clams scan
	$(MAKE) -C dough scan
	$(MAKE) -C pepperoni scan
	$(MAKE) -C sauce scan
	$(MAKE) -C veggies scan
tidy :
	$(MAKE) -C cheese tidy
	$(MAKE) -C clams tidy
	$(MAKE) -C dough tidy
	$(MAKE) -C pepperoni tidy
	$(MAKE) -C sauce tidy
	$(MAKE) -C veggies tidy