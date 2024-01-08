###########################################
#Makefile for my programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn
ARCH = $(shell llvm-config --host-target)
CC = /usr/bin/clang --target=$(ARCH)
CXX = /usr/bin/clang++ --target=$(ARCH)
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : algorithm c c++ design_pattern native operating_system socket stl
arm :
	$(MAKE) -C Learning_ARM
algorithm :
	$(MAKE) -C Learning_Algorithm
c :
	$(MAKE) -C Learning_C
c++ :
	$(MAKE) -C Learning_C++
design_pattern :
	$(MAKE) -C Learning_Design_Pattern
native :
	$(MAKE) -C Learning_Native
operating_system :
	$(MAKE) -C Learning_Operating_System
socket :
	$(MAKE) -C Learning_Socket
stl :
	$(MAKE) -C Learning_STL

format :
	$(MAKE) -C Learning_ARM format
	$(MAKE) -C Learning_Algorithm format
	$(MAKE) -C Learning_C format
	$(MAKE) -C Learning_C++ format
	$(MAKE) -C Learning_Design_Pattern format
	$(MAKE) -C Learning_Native format
	# $(MAKE) -C Learning_Operating_System format
	$(MAKE) -C Learning_Socket format
	$(MAKE) -C Learning_STL format

clean :
	# $(MAKE) -C Learning_ARM clean
	$(MAKE) -C Learning_Algorithm clean
	$(MAKE) -C Learning_C clean
	$(MAKE) -C Learning_C++ clean
	$(MAKE) -C Learning_Design_Pattern clean
	$(MAKE) -C Learning_Native clean
	$(MAKE) -C Learning_Operating_System clean
	$(MAKE) -C Learning_Socket clean
	$(MAKE) -C Learning_STL clean

style :
	clang-format -style=webkit -dump-config > .clang-format

bak :
	git archive --format=tar.gz --prefix=learn/ --output ../learn.tar.gz master