###########################################
#Makefile for my programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : algorithm c c++ design_pattern native operating_system rust socket stl
algorithm :
	$(MAKE) -C Learning_Algorithm
c :
	$(MAKE) -C Learning_C
c++ :
	$(MAKE) -C Learning_C++
design_pattern :
	$(MAKE) -C Learning_Design_Pattern
driver :
	$(MAKE) -C Learning_Driver
native :
	$(MAKE) -C Learning_Native
operating_system :
	$(MAKE) -C Learning_Operating_System
rust :
	$(MAKE) -C Learning_Rust
socket :
	$(MAKE) -C Learning_Socket
stl :
	$(MAKE) -C Learning_STL

format :
	$(MAKE) -C Learning_Algorithm format
	$(MAKE) -C Learning_C format
	$(MAKE) -C Learning_C++ format
	$(MAKE) -C Learning_Design_Pattern format
	$(MAKE) -C Learning_Driver format
	$(MAKE) -C Learning_Native format
	# $(MAKE) -C Learning_Operating_System format
	$(MAKE) -C Learning_Rust format
	$(MAKE) -C Learning_Socket format
	$(MAKE) -C Learning_STL format

clean :
	$(MAKE) -C Learning_Algorithm clean
	$(MAKE) -C Learning_C clean
	$(MAKE) -C Learning_C++ clean
	$(MAKE) -C Learning_Design_Pattern clean
	# $(MAKE) -C Learning_Driver clean
	$(MAKE) -C Learning_Native clean
	$(MAKE) -C Learning_Operating_System clean
	$(MAKE) -C Learning_Rust format clean
	$(MAKE) -C Learning_Socket clean
	$(MAKE) -C Learning_STL clean

style :
	clang-format -style=webkit -dump-config > .clang-format

bak :
	git archive --format=tar.gz --prefix=learn/ --output ../learn.tar.gz master