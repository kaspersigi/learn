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
all : barista barista_with_hook
barista :
	$(MAKE) -C 01.barista
barista_with_hook :
	$(MAKE) -C 02.barista_with_hook

format :
	$(MAKE) -C 01.barista format
	$(MAKE) -C 02.barista_with_hook format

clean :
	$(MAKE) -C 01.barista clean
	$(MAKE) -C 02.barista_with_hook clean

scan :
	$(MAKE) -C 01.barista scan
	$(MAKE) -C 02.barista_with_hook scan

tidy :
	$(MAKE) -C 01.barista tidy
	$(MAKE) -C 02.barista_with_hook tidy