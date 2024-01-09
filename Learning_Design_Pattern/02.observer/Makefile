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
C_FLAGS = -std=c2x -Wall -Wno-unused
CXX_FLAGS = -std=c++2b -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : WeatherStation
WeatherStation : WeatherStation.o subjects.o observers.o
	$(CXX) WeatherStation.o subjects/*.o observers/*.o -o WeatherStation $(CLANGXX_LINK_FLAGS)
	rm -v WeatherStation.o
	$(MAKE) -C subjects clean
	$(MAKE) -C observers clean
WeatherStation.o : WeatherStation.cc WeatherStation.h
	$(CXX) WeatherStation.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
observers.o :
	$(MAKE) -C observers
subjects.o :
	$(MAKE) -C subjects
format :
	$(FORMAT) WeatherStation.cc -style=file -i
	$(FORMAT) WeatherStation.h -style=file -i
	$(FORMAT) interface/DisplayElement.h -style=file -i
	$(FORMAT) interface/Observer.h -style=file -i
	$(FORMAT) interface/Subject.h -style=file -i
	$(MAKE) -C subjects format
	$(MAKE) -C observers format
clean :
	rm -v WeatherStation
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./WeatherStation