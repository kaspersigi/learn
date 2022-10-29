###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
CC = /usr/bin/gcc
CXX = /usr/bin/g++
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c99 -Wall -Wno-unused
CXX_FLAGS = -std=c++0x -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(OBJ)
	$(CXX) $(OBJ) -o $(TRG)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CXX) $(SRC) -c $(CXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) main.cc -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --error-limit=no ./$(TRG)