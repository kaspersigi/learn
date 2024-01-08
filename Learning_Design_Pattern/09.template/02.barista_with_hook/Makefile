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
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : Barista
Barista : Barista.o interface.o beverages.o
	$(CXX) Barista.o interface/*.o beverages/*.o -o Barista $(CLANGXX_LINK_FLAGS)
	rm -v Barista.o
	$(MAKE) -C interface clean
	$(MAKE) -C beverages clean
Barista.o : Barista.cc Barista.h
	$(CXX) Barista.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
beverages.o :
	$(MAKE) -C beverages
format :
	$(FORMAT) Barista.cc -style=file -i
	$(FORMAT) Barista.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C beverages format
clean :
	rm -v Barista
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./Barista