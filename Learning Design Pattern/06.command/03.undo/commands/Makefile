###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
CC = /usr/bin/clang
CXX = /usr/bin/clang++
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -O3
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : LightOffCommand.o LightOnCommand.o NoCommand.o
LightOffCommand.o : LightOffCommand.cc LightOffCommand.h
	$(CXX) LightOffCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
LightOnCommand.o : LightOnCommand.cc LightOnCommand.h
	$(CXX) LightOnCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
NoCommand.o : NoCommand.cc NoCommand.h
	$(CXX) NoCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) LightOffCommand.cc -style=file -i
	$(FORMAT) LightOffCommand.h -style=file -i
	$(FORMAT) LightOnCommand.cc -style=file -i
	$(FORMAT) LightOnCommand.h -style=file -i
	$(FORMAT) NoCommand.cc -style=file -i
	$(FORMAT) NoCommand.h -style=file -i
	$(FORMAT) commands.h -style=file -i
clean :
	rm -v LightOffCommand.o
	rm -v LightOnCommand.o
	rm -v NoCommand.o