###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /mnt/develop/linux/learn/Learning_Multithread
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
all : template atomic mutex condition_variable detach async coroutine threadmanager advancethreadmanager
template :
	$(MAKE) -C 00.template
atomic :
	$(MAKE) -C 01.atomic
mutex :
	$(MAKE) -C 02.mutex
condition_variable :
	$(MAKE) -C 03.condition_variable
detach :
	$(MAKE) -C 04.detach
async :
	$(MAKE) -C 05.async
coroutine :
	$(MAKE) -C 06.coroutine
threadmanager :
	$(MAKE) -C 07.threadmanager
advancethreadmanager :
	$(MAKE) -C 08.advancethreadmanager

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.atomic format
	$(MAKE) -C 02.mutex format
	$(MAKE) -C 03.condition_variable format
	$(MAKE) -C 04.detach format
	$(MAKE) -C 05.async format
	$(MAKE) -C 06.coroutine format
	$(MAKE) -C 07.threadmanager format
	$(MAKE) -C 08.advancethreadmanager format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.atomic clean
	$(MAKE) -C 02.mutex clean
	$(MAKE) -C 03.condition_variable clean
	$(MAKE) -C 04.detach clean
	$(MAKE) -C 05.async clean
	$(MAKE) -C 06.coroutine clean
	$(MAKE) -C 07.threadmanager clean
	$(MAKE) -C 08.advancethreadmanager clean

scan :
	$(MAKE) -C 00.template scan
	$(MAKE) -C 01.atomic scan
	$(MAKE) -C 02.mutex scan
	$(MAKE) -C 03.condition_variable scan
	$(MAKE) -C 04.detach scan
	$(MAKE) -C 05.async scan
	$(MAKE) -C 06.coroutine scan
	$(MAKE) -C 07.threadmanager scan
	$(MAKE) -C 08.advancethreadmanager scan

tidy :
	$(MAKE) -C 00.template tidy
	$(MAKE) -C 01.atomic tidy
	$(MAKE) -C 02.mutex tidy
	$(MAKE) -C 03.condition_variable tidy
	$(MAKE) -C 04.detach tidy
	$(MAKE) -C 05.async tidy
	$(MAKE) -C 06.coroutine tidy
	$(MAKE) -C 07.threadmanager tidy
	$(MAKE) -C 08.advancethreadmanager tidy