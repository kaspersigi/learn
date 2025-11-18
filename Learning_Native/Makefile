###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /mnt/develop/linux/learn/Learning_Native
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
all : template v4l2 xv6_clang xv6_gcc xv6_riscv
template :
	$(MAKE) -C 00.template
v4l2 :
	$(MAKE) -C 01.v4l2
xv6_clang :
	$(MAKE) -C 02.xv6_clang
xv6_gcc :
	$(MAKE) -C 03.xv6_gcc
xv6_riscv :
	$(MAKE) -C 04.xv6_riscv

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.v4l2 format
	$(MAKE) -C 02.xv6_clang format
	$(MAKE) -C 03.xv6_gcc format
	$(MAKE) -C 04.xv6_riscv format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.v4l2 clean
	$(MAKE) -C 02.xv6_clang clean
	$(MAKE) -C 03.xv6_gcc clean
	$(MAKE) -C 04.xv6_riscv clean

scan :
	$(MAKE) -C 00.template scan
	$(MAKE) -C 01.v4l2 scan
	$(MAKE) -C 02.xv6_clang scan
	$(MAKE) -C 03.xv6_gcc scan
	$(MAKE) -C 04.xv6_riscv scan

tidy :
	$(MAKE) -C 00.template tidy
	$(MAKE) -C 01.v4l2 tidy
	# $(MAKE) -C 02.xv6_clang tidy
	# $(MAKE) -C 03.xv6_gcc tidy
	# $(MAKE) -C 04.xv6_riscv tidy