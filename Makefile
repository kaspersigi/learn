###########################################
#Makefile for my programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn
LLVM = -20
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -flto -O3
LIBS = -lpthread
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
all : algorithm android c c++ design_pattern driver multithread native opencl operating_system socket stl
algorithm :
	$(MAKE) -C Learning_Algorithm
android :
	$(MAKE) -C Learning_Android
c :
	$(MAKE) -C Learning_C
c++ :
	$(MAKE) -C Learning_C++
design_pattern :
	$(MAKE) -C Learning_Design_Pattern
driver :
	$(MAKE) -C Learning_Driver
multithread :
	$(MAKE) -C Learning_Multithread
native :
	$(MAKE) -C Learning_Native
opencl :
	$(MAKE) -C Learning_OpenCL
operating_system :
	$(MAKE) -C Learning_Operating_System
socket :
	$(MAKE) -C Learning_Socket
stl :
	$(MAKE) -C Learning_STL

format :
	$(MAKE) -C Learning_Algorithm format
	$(MAKE) -C Learning_Android format
	$(MAKE) -C Learning_C format
	$(MAKE) -C Learning_C++ format
	$(MAKE) -C Learning_Design_Pattern format
	$(MAKE) -C Learning_Driver format
	$(MAKE) -C Learning_Multithread format
	$(MAKE) -C Learning_Native format
	$(MAKE) -C Learning_OpenCL format
	# $(MAKE) -C Learning_Operating_System format
	$(MAKE) -C Learning_Socket format
	$(MAKE) -C Learning_STL format

clean :
	$(MAKE) -C Learning_Algorithm clean
	$(MAKE) -C Learning_Android clean
	$(MAKE) -C Learning_C clean
	$(MAKE) -C Learning_C++ clean
	$(MAKE) -C Learning_Design_Pattern clean
	$(MAKE) -C Learning_Driver clean
	$(MAKE) -C Learning_Multithread clean
	$(MAKE) -C Learning_Native clean
	$(MAKE) -C Learning_OpenCL clean
	$(MAKE) -C Learning_Operating_System clean
	$(MAKE) -C Learning_Socket clean
	$(MAKE) -C Learning_STL clean

style :
	clang-format -style=webkit -dump-config > .clang-format

bak :
	git archive --format=tar.gz --prefix=learn/ --output ../learn.tar.gz master