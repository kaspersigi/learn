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
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : Amplifier.o CdPlayer.o DvdPlayer.o PopcornPopper.o Projector.o Screen.o TheaterLights.o Tuner.o
Amplifier.o : Amplifier.cc Amplifier.h
	$(CXX) Amplifier.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
CdPlayer.o : CdPlayer.cc CdPlayer.h
	$(CXX) CdPlayer.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
DvdPlayer.o : DvdPlayer.cc DvdPlayer.h
	$(CXX) DvdPlayer.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
PopcornPopper.o : PopcornPopper.cc PopcornPopper.h
	$(CXX) PopcornPopper.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Projector.o : Projector.cc Projector.h
	$(CXX) Projector.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Screen.o : Screen.cc Screen.h
	$(CXX) Screen.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
TheaterLights.o : TheaterLights.cc TheaterLights.h
	$(CXX) TheaterLights.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Tuner.o : Tuner.cc Tuner.h
	$(CXX) Tuner.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) Amplifier.cc -style=file -i
	$(FORMAT) Amplifier.h -style=file -i
	$(FORMAT) CdPlayer.cc -style=file -i
	$(FORMAT) CdPlayer.h -style=file -i
	$(FORMAT) DvdPlayer.cc -style=file -i
	$(FORMAT) DvdPlayer.h -style=file -i
	$(FORMAT) PopcornPopper.cc -style=file -i
	$(FORMAT) PopcornPopper.h -style=file -i
	$(FORMAT) Projector.cc -style=file -i
	$(FORMAT) Projector.h -style=file -i
	$(FORMAT) Screen.cc -style=file -i
	$(FORMAT) Screen.h -style=file -i
	$(FORMAT) TheaterLights.cc -style=file -i
	$(FORMAT) TheaterLights.h -style=file -i
	$(FORMAT) Tuner.cc -style=file -i
	$(FORMAT) Tuner.h -style=file -i
	$(FORMAT) devices.h -style=file -i
clean :
	rm -v Amplifier.o CdPlayer.o DvdPlayer.o PopcornPopper.o Projector.o Screen.o TheaterLights.o Tuner.o