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
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : c c++ design_pattern native driver operating_system socket stl
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
socket :
	$(MAKE) -C Learning_Socket
stl :
	$(MAKE) -C Learning_STL

format :
	$(MAKE) -C Learning_C format
	$(MAKE) -C Learning_C++ format
	$(MAKE) -C Learning_Design_Pattern format
	$(MAKE) -C Learning_Driver format
	$(MAKE) -C Learning_Native format
	# $(MAKE) -C Learning_Operating_System format
	$(MAKE) -C Learning_Socket format
	$(MAKE) -C Learning_STL format

clean :
	$(MAKE) -C Learning_C clean
	$(MAKE) -C Learning_C++ clean
	$(MAKE) -C Learning_Design_Pattern clean
	$(MAKE) -C Learning_Driver clean
	$(MAKE) -C Learning_Native clean
	$(MAKE) -C Learning_Operating_System clean
	$(MAKE) -C Learning_Socket clean
	$(MAKE) -C Learning_STL clean

bak :
	git archive --format=tar.gz --output ../learn.tar.gz master