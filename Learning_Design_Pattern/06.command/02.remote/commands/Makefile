###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = 17
CONFIG = llvm-config-$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang-$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++-$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format-$(LLVM)
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : GarageDoorDownCommand.o GarageDoorUpCommand.o HottubOffCommand.o HottubOnCommand.o LightOffCommand.o LightOnCommand.o LivingroomLightOffCommand.o LivingroomLightOnCommand.o StereoOffCommand.o StereoOnWithCDCommand.o NoCommand.o
GarageDoorDownCommand.o : GarageDoorDownCommand.cc GarageDoorDownCommand.h
	$(CXX) GarageDoorDownCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
GarageDoorUpCommand.o : GarageDoorUpCommand.cc GarageDoorUpCommand.h
	$(CXX) GarageDoorUpCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
HottubOffCommand.o : HottubOffCommand.cc HottubOffCommand.h
	$(CXX) HottubOffCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
HottubOnCommand.o : HottubOnCommand.cc HottubOnCommand.h
	$(CXX) HottubOnCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
LightOffCommand.o : LightOffCommand.cc LightOffCommand.h
	$(CXX) LightOffCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
LightOnCommand.o : LightOnCommand.cc LightOnCommand.h
	$(CXX) LightOnCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
LivingroomLightOffCommand.o : LivingroomLightOffCommand.cc LivingroomLightOffCommand.h
	$(CXX) LivingroomLightOffCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
LivingroomLightOnCommand.o : LivingroomLightOnCommand.cc LivingroomLightOnCommand.h
	$(CXX) LivingroomLightOnCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
StereoOffCommand.o : StereoOffCommand.cc StereoOffCommand.h
	$(CXX) StereoOffCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
StereoOnWithCDCommand.o : StereoOnWithCDCommand.cc StereoOnWithCDCommand.h
	$(CXX) StereoOnWithCDCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
NoCommand.o : NoCommand.cc NoCommand.h
	$(CXX) NoCommand.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) GarageDoorDownCommand.cc -style=file -i
	$(FORMAT) GarageDoorDownCommand.h -style=file -i
	$(FORMAT) GarageDoorUpCommand.cc -style=file -i
	$(FORMAT) GarageDoorUpCommand.h -style=file -i
	$(FORMAT) HottubOffCommand.cc -style=file -i
	$(FORMAT) HottubOffCommand.h -style=file -i
	$(FORMAT) HottubOnCommand.cc -style=file -i
	$(FORMAT) HottubOnCommand.h -style=file -i
	$(FORMAT) LightOffCommand.cc -style=file -i
	$(FORMAT) LightOffCommand.h -style=file -i
	$(FORMAT) LightOnCommand.cc -style=file -i
	$(FORMAT) LightOnCommand.h -style=file -i
	$(FORMAT) LivingroomLightOffCommand.cc -style=file -i
	$(FORMAT) LivingroomLightOffCommand.h -style=file -i
	$(FORMAT) LivingroomLightOnCommand.cc -style=file -i
	$(FORMAT) LivingroomLightOnCommand.h -style=file -i
	$(FORMAT) StereoOffCommand.cc -style=file -i
	$(FORMAT) StereoOffCommand.h -style=file -i
	$(FORMAT) StereoOnWithCDCommand.cc -style=file -i
	$(FORMAT) StereoOnWithCDCommand.h -style=file -i
	$(FORMAT) NoCommand.cc -style=file -i
	$(FORMAT) NoCommand.h -style=file -i
	$(FORMAT) commands.h -style=file -i
clean :
	rm -v GarageDoorDownCommand.o GarageDoorUpCommand.o HottubOffCommand.o HottubOnCommand.o LightOffCommand.o LightOnCommand.o LivingroomLightOffCommand.o LivingroomLightOnCommand.o StereoOffCommand.o StereoOnWithCDCommand.o NoCommand.o