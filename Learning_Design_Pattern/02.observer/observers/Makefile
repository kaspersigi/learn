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
all : CurrentConditionsDisplay.o ForecastDisplay.o HeatIndexDisplay.o StatisticsDisplay.o
CurrentConditionsDisplay.o : CurrentConditionsDisplay.cc CurrentConditionsDisplay.h
	$(CXX) CurrentConditionsDisplay.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ForecastDisplay.o : ForecastDisplay.cc ForecastDisplay.h
	$(CXX) ForecastDisplay.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
HeatIndexDisplay.o : HeatIndexDisplay.cc HeatIndexDisplay.h
	$(CXX) HeatIndexDisplay.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
StatisticsDisplay.o : StatisticsDisplay.cc StatisticsDisplay.h
	$(CXX) StatisticsDisplay.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) observers.h -style=file -i
	$(FORMAT) CurrentConditionsDisplay.cc -style=file -i
	$(FORMAT) CurrentConditionsDisplay.h -style=file -i
	$(FORMAT) ForecastDisplay.cc -style=file -i
	$(FORMAT) ForecastDisplay.h -style=file -i
	$(FORMAT) HeatIndexDisplay.cc -style=file -i
	$(FORMAT) HeatIndexDisplay.h -style=file -i
	$(FORMAT) StatisticsDisplay.cc -style=file -i
	$(FORMAT) StatisticsDisplay.h -style=file -i
clean :
	rm -v CurrentConditionsDisplay.o ForecastDisplay.o HeatIndexDisplay.o StatisticsDisplay.o