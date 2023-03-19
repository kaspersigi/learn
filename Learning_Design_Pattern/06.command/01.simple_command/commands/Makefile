###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
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
all : LightOnCommand.o LightOffCommand.o GarageDoorOpenCommand.o
LightOnCommand.o : LightOnCommand.cc LightOnCommand.h
	$(CXX) LightOnCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
LightOffCommand.o : LightOffCommand.cc LightOffCommand.h
	$(CXX) LightOffCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
GarageDoorOpenCommand.o : GarageDoorOpenCommand.cc GarageDoorOpenCommand.h
	$(CXX) GarageDoorOpenCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) LightOnCommand.cc -style=file -i
	$(FORMAT) LightOnCommand.h -style=file -i
	$(FORMAT) LightOffCommand.cc -style=file -i
	$(FORMAT) LightOffCommand.h -style=file -i
	$(FORMAT) GarageDoorOpenCommand.cc -style=file -i
	$(FORMAT) GarageDoorOpenCommand.h -style=file -i
	$(FORMAT) commands.h -style=file -i
clean :
	rm -v LightOnCommand.o LightOffCommand.o GarageDoorOpenCommand.o