###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
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
all : CeilingFan.o Hottub.o GarageDoor.o Light.o Stereo.o TV.o
CeilingFan.o : CeilingFan.cc CeilingFan.h
	$(CXX) CeilingFan.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Hottub.o : Hottub.cc Hottub.h
	$(CXX) Hottub.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
GarageDoor.o : GarageDoor.cc GarageDoor.h
	$(CXX) GarageDoor.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Light.o : Light.cc Light.h
	$(CXX) Light.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Stereo.o : Stereo.cc Stereo.h
	$(CXX) Stereo.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
TV.o : TV.cc TV.h
	$(CXX) TV.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) CeilingFan.cc -style=file -i
	$(FORMAT) CeilingFan.h -style=file -i
	$(FORMAT) Hottub.cc -style=file -i
	$(FORMAT) Hottub.h -style=file -i
	$(FORMAT) GarageDoor.cc -style=file -i
	$(FORMAT) GarageDoor.h -style=file -i
	$(FORMAT) Light.cc -style=file -i
	$(FORMAT) Light.h -style=file -i
	$(FORMAT) Stereo.cc -style=file -i
	$(FORMAT) Stereo.h -style=file -i
	$(FORMAT) TV.cc -style=file -i
	$(FORMAT) TV.h -style=file -i
	$(FORMAT) devices.h -style=file -i
clean :
	rm -v CeilingFan.o Hottub.o GarageDoor.o Light.o Stereo.o TV.o