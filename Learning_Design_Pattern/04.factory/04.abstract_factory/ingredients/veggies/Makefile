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
all : BlackOlives.o Eggplant.o Garlic.o Mushroom.o Onion.o RedPepper.o Spinach.o
BlackOlives.o : BlackOlives.cc BlackOlives.h
	$(CXX) BlackOlives.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Eggplant.o : Eggplant.cc Eggplant.h
	$(CXX) Eggplant.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Garlic.o : Garlic.cc Garlic.h
	$(CXX) Garlic.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Mushroom.o : Mushroom.cc Mushroom.h
	$(CXX) Mushroom.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Onion.o : Onion.cc Onion.h
	$(CXX) Onion.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
RedPepper.o : RedPepper.cc RedPepper.h
	$(CXX) RedPepper.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Spinach.o : Spinach.cc Spinach.h
	$(CXX) Spinach.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) BlackOlives.cc -style=file -i
	$(FORMAT) BlackOlives.h -style=file -i
	$(FORMAT) Eggplant.cc -style=file -i
	$(FORMAT) Eggplant.h -style=file -i
	$(FORMAT) Garlic.cc -style=file -i
	$(FORMAT) Garlic.h -style=file -i
	$(FORMAT) Mushroom.cc -style=file -i
	$(FORMAT) Mushroom.h -style=file -i
	$(FORMAT) Onion.cc -style=file -i
	$(FORMAT) Onion.h -style=file -i
	$(FORMAT) RedPepper.cc -style=file -i
	$(FORMAT) RedPepper.h -style=file -i
	$(FORMAT) Spinach.cc -style=file -i
	$(FORMAT) Spinach.h -style=file -i
clean :
	rm -v BlackOlives.o Eggplant.o Garlic.o Mushroom.o Onion.o RedPepper.o Spinach.o